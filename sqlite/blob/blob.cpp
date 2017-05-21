#include <string.h>
#include <stdio.h>
#include "sqlite3.h"

sqlite3* db;

int first_row;

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names) {

  int i;

  int* nof_records = (int*) p_data;
  (*nof_records)++;

  if (first_row) {
    first_row = 0;

    for (i=0; i < num_fields; i++) {
      printf("%20s", p_col_names[i]);
    }

    printf("\n");
    for (i=0; i< num_fields*20; i++) {
      printf("=");
    }
    printf("\n");
  }

  for(i=0; i < num_fields; i++) {
    if (p_fields[i]) {
      printf("%20s", p_fields[i]);
    }
    else {
      printf("%20s", " ");
    }
  }

  printf("\n");
  return 0;
}


void select_stmt(const char* stmt) {
  char *errmsg;
  int   ret;
  int   nrecs = 0;

  first_row = 1;

  ret = sqlite3_exec(db, stmt, select_callback, &nrecs, &errmsg);

  if(ret!=SQLITE_OK) {
    printf("Error in select statement %s [%s].\n", stmt, errmsg);
  }
  else {
    printf("\n   %d records returned.\n", nrecs);
  }
}

void sql_stmt(const char* stmt) {
  char *errmsg;
  int   ret;

  ret = sqlite3_exec(db, stmt, 0, 0, &errmsg);

  if(ret != SQLITE_OK) {
    printf("Error in statement: %s [%s].\n", stmt, errmsg);
  }
}

struct InsertData {
	const char* val1; // text
	int val1Len;
	const void* val2; // blob
	int val2Len;
};
char BIN0123[] = {0x00, 0x01, 0x02, 0x03};
InsertData DATA_ARRAY[] = {
	{"f_blob", 6, "f\0blob", 7},
	{"blob_data", 9, "blob\0data", 10},
	{"0123", 4, BIN0123, 4},  // rowid:3
};
#define DATA_NUM (sizeof(DATA_ARRAY)/sizeof(InsertData))

int insert_stmt()
{
  sqlite3_stmt *stmt;

  if ( sqlite3_prepare(
         db, 
         "insert into tbl_test values (?,?)",  // stmt
        -1, // If than zero, then stmt is read up to the first nul terminator
        &stmt,
         0  // Pointer to unused portion of stmt
       )
       != SQLITE_OK) {
    printf("\nCould not prepare statement.");
    return 1;
  }

//  printf("\nThe statement has %d wildcards\n", sqlite3_bind_parameter_count(stmt));

  for (int i = 0; i < DATA_NUM; i++) {

	  if (sqlite3_bind_text(
			  stmt,
			  1,  // Index of wildcard
			  DATA_ARRAY[i].val1,
			  DATA_ARRAY[i].val1Len,
			  NULL
			  )
		  != SQLITE_OK) {
		  printf("\nCould not bind double.\n");
		  return 1;
	  }
	  if (sqlite3_bind_blob(
			  stmt,
			  2,  // Index of wildcard
			  DATA_ARRAY[i].val2,
			  DATA_ARRAY[i].val2Len,
			  NULL
			  )
		  != SQLITE_OK) {
		  printf("\nCould not bind int.\n");
		  return 1;
	  }
	  if (sqlite3_step(stmt) != SQLITE_DONE) {
		  printf("\nCould not step (execute) stmt.\n");
		  return 1;
	  }

	  sqlite3_reset(stmt);
  }

  return 0;
}


int select_bind()
{
  sqlite3_stmt *stmt;

  if ( sqlite3_prepare(
         db, 
//         "select rowid, f_text, hex(f_blob), hex(?) from tbl_test",
         "select rowid, f_text, hex(f_blob) from tbl_test where hex(f_blob) like \"%\"||hex(?)||\"%\" ",  // stmt
        -1, // If than zero, then stmt is read up to the first nul terminator
        &stmt,
         0  // Pointer to unused portion of stmt
       )
       != SQLITE_OK) {
    printf("\nCould not prepare statement.");
    return 1;
  }

  printf("\nThe statement has %d wildcards\n", sqlite3_bind_parameter_count(stmt));

  if (sqlite3_bind_blob(
        stmt,
        1,  // Index of wildcard
        BIN0123,
		4,
		NULL
        )
      != SQLITE_OK) {
    printf("\nCould not bind double.\n");
    return 1;
  }

  int ret = SQLITE_ROW;
  int count = 0;
#if 1
  while ((ret = sqlite3_step(stmt)) == SQLITE_ROW) {
	  int  id = sqlite3_column_int(stmt, 0);
	  printf("count: %d, rowid: %d\n", count, id);
	  count++;
  }
  if (ret != SQLITE_OK) {
	  printf("\nCould not step (execute) stmt: %d\n", ret);
  } else {
	  printf("step OK\n");
  }
#else
  char *errmsg;
  int   nrecs = 0;
  first_row = 1;
  ret = sqlite3_exec(db, stmt, select_callback, &nrecs, &errmsg);
  if(ret!=SQLITE_OK) {
    printf("Error in select statement %s [%s].\n", stmt, errmsg);
  }
  else {
    printf("\n   %d records returned.\n", nrecs);
  }
#endif
  return 0;
}

int main() {
  sqlite3_open("./blob_test.db", &db);

  if(db == 0) {
    printf("\nCould not open database.");
    return 1;
  }

  sql_stmt("create table tbl_test (f_text TEXT, f_blob BLOB)");

  insert_stmt();
//  select_stmt("select rowid, f_text, hex(f_blob) from tbl_test");

  printf("\n");
  select_bind();

  sqlite3_close(db);
  return 0;
}

// MEMO:
// 
// >select rowid, hex(f_blob) from tbl_test where hex(f_blob) like "%00%";
// returns record which has '\0' in blob field.
// NOTE: hex() can be used to generate hexdecimal string in like clause".
//   >select rowid, hex(f_blob) from tbl_test where hex(f_blob) like "%"||hex(?)||"%";
//
//
// >select rowid, hex(f_blob) from tbl_test where f_blob like "%blob%";
// only "blob\0data" hits.
//
