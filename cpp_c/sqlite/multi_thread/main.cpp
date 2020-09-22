#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <assert.h>

#include <unistd.h> // unlink
#include <time.h>

#define DBNAME "test.db"


#define BUF_SIZE (256 * 1024) // 256 KB
#define TEXT_VALUE_BUF_SIZE (32 * 1024) // each text val: 32KB


static int total_sql_num = 1000;
static int max_sql_in_trans = 100;
static char sql_buf[BUF_SIZE];
static bool new_db = true;
static const char* sql_template = "INSERT INTO tbl1 VALUES (%d, %1d%1d%1d, \"test%d\");";
static const char* db_name = DBNAME;
static bool option_verbose = false;
#define MAX_CREATE_SQL_COUNT 10
static int sql_create_count = 0;
static int64_t soft_heap_limit = 0; // disable limit.
static bool param_text = false; // to set PARAM_OPT_x_TEXT
static const char *sql_create_table[MAX_CREATE_SQL_COUNT + 1] = {
	"CREATE TABLE IF NOT EXISTS tbl1 (id , c1_int, c2_text);",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL, // terminator
};

enum ParamOptType {
	PARAM_OPT_ID,
	PARAM_OPT_MOD,
	PARAM_OPT_DIV,
	PARAM_OPT_1K_TEXT,
};
struct ParamOpt {
	ParamOptType type;
	int val;
};
#define PARAM_NUM 10
static ParamOpt converted_param[PARAM_NUM] = {
	{PARAM_OPT_ID, 0},  // through id
	{PARAM_OPT_MOD, 10}, // mod 10
	{PARAM_OPT_MOD, 10}, // mod 10
	{PARAM_OPT_MOD, 10}, // mod 10
	{PARAM_OPT_ID, 0},  // through id
	{PARAM_OPT_ID, 0},  // through id
	{PARAM_OPT_ID, 0},  // through id
	{PARAM_OPT_ID, 0},  // through id
	{PARAM_OPT_ID, 0},  // through id
	{PARAM_OPT_ID, 0},  // through id
};
static int value_gen(int sql_id, int param_id) //  0
{
	assert(param_id >= 0 && param_id < PARAM_NUM);
	assert(!param_text);
	switch (converted_param[param_id].type) {
	case PARAM_OPT_ID:
		// through
		return sql_id;
	case PARAM_OPT_MOD:
		// positive value => mod
		return sql_id % converted_param[param_id].val;
	case PARAM_OPT_DIV:
		return sql_id / converted_param[param_id].val;
	default:
		assert(false);
		break;
	}
	return -1;
}
static char TEXT_VAL_BUF[PARAM_NUM][TEXT_VALUE_BUF_SIZE] = {"", "", "", "", "", "", "", "", "", ""};
static const char* value_gen_text(int sql_id, int param_id)
{
	assert(param_id >= 0 && param_id < PARAM_NUM);
	assert(param_text);
	switch (converted_param[param_id].type) {
	case PARAM_OPT_1K_TEXT:
		return TEXT_VAL_BUF[param_id];
	default:
		//assert(false); XXX: default params run this path.
		break;
	}
	//return NULL;
	return "";
}
static int set_conveted_param(const char* arg, int param_id)
{
	assert(param_id >= 0 && param_id < PARAM_NUM);
	if (strcmp(arg, "0") == 0
		|| strcmp(arg, "id") == 0
		|| strcmp(arg, "sql_id") == 0) {
			printf("\tset_converted_param(): sql_id for: %d\n", param_id);
			converted_param[param_id].type = PARAM_OPT_ID;
			converted_param[param_id].val = 0;
			return 0;
	} else if (arg[0] == 'm'
		&& arg[1] == 'o'
		&& arg[2] == 'd') {
			converted_param[param_id].type = PARAM_OPT_MOD;
			converted_param[param_id].val = atoi(&arg[3]);
			printf("\tset_converted_param(): mod %d for: %d\n", converted_param[param_id].val, param_id);
			return 0;
	} else if (arg[0] == 'd'
		&& arg[1] == 'i'
		&& arg[2] == 'v') {
			converted_param[param_id].type = PARAM_OPT_DIV;
			converted_param[param_id].val = atoi(&arg[3]);
			printf("\tset_converted_param(): div %d for: %d\n", converted_param[param_id].val, param_id);
			return 0;
	} else if (arg[0] == '1'
		&& arg[1] == 'k') {
			param_text = true;
			converted_param[param_id].type = PARAM_OPT_1K_TEXT;
			converted_param[param_id].val = atoi(&arg[2]);
			printf("\tset_converted_param(): %d kb_text for: %d\n", converted_param[param_id].val, param_id);
			memset(TEXT_VAL_BUF[param_id], '1' + param_id, 1024 * converted_param[param_id].val);
			TEXT_VAL_BUF[param_id][1024 * converted_param[param_id].val] = '\0';
			return 0;
	}
	printf("error: unknown param: %s\n", arg);
	assert(false);
	return -1;
}


#define VERBOSE_PRINTF(...) \
	if (option_verbose) {   \
		printf("[VERBOSE]: "); \
		printf(__VA_ARGS__); \
	}

static int
cb_sql ( void *NotUsed, int argc, char **argv, char **azColName )
{
	// print
	for ( int i = 0; i < argc; i++ )
	{
		printf ( "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL" );
	}
	printf ( "\n" );
	return 0;
}

int
start_transaction(sqlite3 *db)
{
	int ret = 0;
	char *zErrMsg = 0;

	VERBOSE_PRINTF("BEGIN TRANSACTION\n");
	ret = sqlite3_exec(db, "BEGIN TRANSACTION",cb_sql, 0, &zErrMsg);
	if ( ret != SQLITE_OK )
	{
		printf("start_transaction() SQL: %s", "BEGIN TRANSACTION");
		printf ( "SQL error: %s\n", zErrMsg );
		sqlite3_free ( zErrMsg );
		return ret;
	}
	return 0;
}
int
end_transaction ( sqlite3 *db, int ret )
{
	char *zErrMsg = 0;

	VERBOSE_PRINTF("%s\n", ret ? "ROLLBACK" : "COMMIT");
	int ret2 = sqlite3_exec ( db, ret ? "ROLLBACK" : "COMMIT", cb_sql, 0, &zErrMsg );
	if ( ret2 != SQLITE_OK )
	{
		printf("end_transaction() SQL: %s", ret ? "ROLLBACK" : "COMMIT");
		printf ( "%s error: %s\n", ret ? "ROLLBACK" : "COMMIT", zErrMsg );
		sqlite3_free ( zErrMsg );
	}

	return ret;
}

int
exec_sql ( sqlite3 *db, const char *sql )
{
	int ret = 0;
	char *zErrMsg = 0;

	VERBOSE_PRINTF("%s\n", sql);
	ret = sqlite3_exec ( db, sql, cb_sql, 0, &zErrMsg );
	if ( ret != SQLITE_OK ) {
		printf("exec_sql() SQL: %s", sql);
		printf ( "SQL error: ret=%d, msg=%s\n", ret, zErrMsg );
		sqlite3_free ( zErrMsg );
		return ret;
	}

	return ret;
}


int
exec_sql_list ( sqlite3 *db, const char **sqls )
{
	VERBOSE_PRINTF("exec_sql_list()\n");
	int ret = 0;
	char *zErrMsg = 0;

	for ( int i = 0; sqls[i]; i++ )
	{
		printf("sqls[%d] : %s\n", i, sqls[i]);
		ret = exec_sql ( db, sqls[i] );
		if ( ret != SQLITE_OK )
		{
			printf ( "exec_sql error: ret=%d\n", ret);
			sqlite3_free ( zErrMsg );
			break;
		}
	}

	printf("sqlite3_memory_highwater(): %lld\n", sqlite3_memory_highwater(true));

	return ret;
}

int
exec_sql_list_in_transaction ( sqlite3 *db, const char **sqls )
{
	VERBOSE_PRINTF("exec_sql_list_in_transaction()\n");
	int ret = 0;
	ret = start_transaction(db);
	if (ret) {
		return ret;
	}
	ret = exec_sql_list(db, sqls);
	if (ret) {
		//return ret;
	}
	int ret2 = end_transaction(db, ret);
	if (ret) {
		return ret;
	}
	return ret2;
}

void fill_sql(int sql_id)
{
	if (param_text) {
		snprintf(sql_buf, BUF_SIZE, 
			sql_template,
			value_gen_text(sql_id, 0),
			value_gen_text(sql_id, 1),
			value_gen_text(sql_id, 2),
			value_gen_text(sql_id, 3),
			value_gen_text(sql_id, 4),
			value_gen_text(sql_id, 5),
			value_gen_text(sql_id, 6),
			value_gen_text(sql_id, 7),
			value_gen_text(sql_id, 8),
			value_gen_text(sql_id, 9));
		return;
	}
	snprintf(sql_buf, BUF_SIZE, 
			 sql_template,
			 value_gen(sql_id, 0),  // sql_id
			 value_gen(sql_id, 1),  // mod10
			 value_gen(sql_id, 2),  // mod10
			 value_gen(sql_id, 3),  // mod10
			 value_gen(sql_id, 4),  // sql_id
			 value_gen(sql_id, 5),  // sql_id
			 value_gen(sql_id, 6),  // sql_id
			 value_gen(sql_id, 7),  // sql_id
			 value_gen(sql_id, 8),  // sql_id
			 value_gen(sql_id, 9)); // sql_id
	return;
}

// arg1: total_sql_num
// arg2: max_sql_in_transaction
// arg3: new_db: 1: create, 0: use existing.
// arg4: sql_template: 1 line sql VA_ARGS: sql_id, mod10, mod10, mod10, sql_id;
// arg5: db_name: default "/app0/test.db"
// arg6 or follower: option
//   options: 
//	     -v: enable verbose print (default false)
//       -c SQL: specify table creation SQL. NOTE: that arg3 must be 1.
//               multiple SQLs can be set with multiple -c options.
//       -1..9 PARAM_VAL: specify or generate va_args for sql_template
//                        "sql_id", "mod?", "div?" (? can be any number).
//                        "1k?" for ?KB text (e.g. 1k2 => 2KB, 1k10 => 10KB).
//       -l SIZE: limit heap with sqlite3_soft_heap_limit64(SIZE).
int check_args(int argc, char** argv)
{
	if (argc >= 2) {
		total_sql_num = atoi(argv[1]);
	}
	if (argc >= 3) {
		max_sql_in_trans = atoi(argv[2]);
	}
	if (argc >= 4) {
		new_db = atoi(argv[3]);
	}
	if (argc >= 5) {
		sql_template = argv[4];
	}
	if (argc >= 6) {
		db_name = argv[5];
	}
	int arg_index = 6;
	while (argc > arg_index) {
		if (argv[arg_index][0] != '-') {
			printf ("error: 6th or following arguments must be a option setting.\n");
			return -1;
		}
		if (argv[arg_index][1] == 'v' || argv[arg_index][1] == 'V') {
			option_verbose = true;
		} else if (argv[arg_index][1] == 'l' || argv[arg_index][1] == 'L') {
			arg_index++;
			if (argc <= arg_index) {
				printf("error: -l option requires a limit size.\n");
				return -1;
			}
			soft_heap_limit = atoll(argv[arg_index]);
			VERBOSE_PRINTF("set soft heap limit: %ld\n", soft_heap_limit);
		} else if (argv[arg_index][1] == 'c' || argv[arg_index][1] == 'C') {
			arg_index++;
			if (argc <= arg_index) {
				printf("error: -c option requires a creation SQL.\n");
				return -1;
			}
			if (!new_db) {
				printf("error: 2nd argument (new_db) must be 1 for -c option .\n");
				return -1;
			}
			if (sql_create_count >= MAX_CREATE_SQL_COUNT) {
				printf("error: too many creation SQL. count: %d\n", sql_create_count);
				return -1;
			}
			printf("\tcreation SQL: %s\n", argv[arg_index]);
			sql_create_table[sql_create_count++] = argv[arg_index];
		} else if (argv[arg_index][1] >= '1' && argv[arg_index][1] <= '9') {
			int param_id = argv[arg_index][1] - '1';
			arg_index++;
			if (argc <= arg_index) {
				printf("error: -1..5 option requires param option (\"sql_id\" or \"modXX\").\n");
				return -1;
			}
			printf("\tparam option[%d]: %s\n", param_id, argv[arg_index]);
			if (set_conveted_param(argv[arg_index], param_id)) {
				// error.
				return -1;
			}
		} else {
			printf("error: unknown option: %s\n", argv[arg_index]);
			return -1;
		}
		arg_index++;
	}
	printf("\n\nMemConsumptionCheck:\n");
	printf("start: total_sql_num: %d, max_sql_in_trans: %d, new_db: %d\n", 
		total_sql_num, max_sql_in_trans, new_db);
	printf("sql_template: %s\n", sql_template);
	//snprintf(sql_buf, BUF_SIZE, sql_template, 1, 1, 1, 1, 1);
	fill_sql(1);
	printf("\tsample: %s\n", sql_buf);
	printf("db_name: %s\n", db_name);
	//printf("soft_heap_limit: %ld\n", soft_heap_limit);
	return 0;
}

int main ( int argc, char **argv )
{
	int ret = check_args(argc, argv);
	if (ret) {
		printf("invalid argument error!\n");
		return -1;
	}

	if (new_db) {
		unlink(db_name);
	}
	soft_heap_limit = sqlite3_soft_heap_limit64(soft_heap_limit);
	if ( soft_heap_limit < 0 ) {
		ret = soft_heap_limit;
		printf("sqlite3_soft_heap_limit() error: %x", ret);
	} else {
		printf("sqlite3_soft_heap_limit64(): prev: %ld (byte) is set to: %lld (byte).\n", soft_heap_limit, sqlite3_soft_heap_limit64(-1));
	}


	sqlite3 *db = NULL;
	ret = sqlite3_open_v2 (db_name, &db, 
		SQLITE_OPEN_CREATE|SQLITE_OPEN_READWRITE, 
		NULL);
	if ( ret != SQLITE_OK )
	{
		printf ( "Can't open database: %s\n", sqlite3_errmsg ( db ) );
		return -1;
	}

	if (new_db) {
		// create table, transaction is useful for speed optimization
		printf("== execute sql_create_table ==\n");
		exec_sql_list_in_transaction(db, sql_create_table);
	} else {
		printf("== use existing db: %s ==\n", db_name);
	}

	int sql_count = 0;
	int trans_count = 0;
	uint64_t total_time = 0;
	int64_t max_highwater = 0;
	uint64_t total_highwater = 0;
	do {
		uint64_t start_time = clock();
		ret = start_transaction(db);
		if (ret) {
			printf("start_transaction() err: %x\n", ret);
			break;
		}
		int trans_sql_count = 0;
		trans_count++;
		do {
			fill_sql(sql_count);
			ret = exec_sql(db, sql_buf);
			if (ret) {
				break;
			}
			sql_count++;
			trans_sql_count++;
		} while (sql_count < total_sql_num 
				 && trans_sql_count < max_sql_in_trans);

		ret = end_transaction(db, ret);
		if (ret) {
			printf("end_transaction() err: %x\n", ret);
			break;
		}
		uint64_t end_time = clock();
		total_time += end_time - start_time;

		printf("[%d] th transaction is end. operated sql num: %d, time: %lu (us)", trans_count, sql_count, end_time - start_time);
		printf("\t: sqlite3_memory_used(): %lld", sqlite3_memory_used());
		int64_t highwater = sqlite3_memory_highwater(true);
		if (max_highwater < highwater) {
			max_highwater = highwater;
		}
		total_highwater += highwater;
		printf("\t: sqlite3_memory_highwater(true): %ld\n", highwater);
	} while (sql_count < total_sql_num);
	printf("operated sql count: %d, transaction count: %d\n", sql_count, trans_count);
	printf("total elapsed time: %lu (us)\n", total_time);
	if (trans_count != 0) {
		printf("maximum memory highwater: %ld, average high water / transaction: %lu\n", max_highwater, total_highwater / trans_count);
	}

/*
	// select
	const char *sql_select[] =
	{
		"SELECT * FROM tbl1;", // select all
		"SELECT id, c1_int FROM tbl1 WHERE 1 < id;", // select 1 < id
		NULL, // terminater
	};
	printf("\n== execute sql_select ==\n");
	exec_sql(db, sql_select);
*/
	sqlite3_close ( db );

	return 0;
}

