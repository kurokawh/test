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

int select_bind()
{
  sqlite3_stmt *stmt;

  if ( sqlite3_prepare(
         db, 
         "insert into foo values (?,?)",  // stmt
//         "select ?,? from foo",  // stmt
        -1, // If than zero, then stmt is read up to the first nul terminator
        &stmt,
         0  // Pointer to unused portion of stmt
       )
       != SQLITE_OK) {
    printf("\nCould not prepare statement.");
    return 1;
  }

  printf("\nThe statement has %d wildcards\n", sqlite3_bind_parameter_count(stmt));

  if (sqlite3_bind_text(
        stmt,
        1,  // Index of wildcard
        "bar",
		3,
		NULL
        )
      != SQLITE_OK) {
    printf("\nCould not bind double.\n");
    return 1;
  }

  if (sqlite3_bind_text(
        stmt,
        2,  // Index of wildcard
        "baz",
		3,
		NULL
        )
      != SQLITE_OK) {
    printf("\nCould not bind int.\n");
    return 1;
  }

  int   ret;
#if 1
  ret =sqlite3_step(stmt);
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


int insert_and_select()
{
  sqlite3_stmt *stmt;

  if ( sqlite3_prepare(
         db, 
         "insert into foo values (?,?)",  // stmt
        -1, // If than zero, then stmt is read up to the first nul terminator
        &stmt,
         0  // Pointer to unused portion of stmt
       )
       != SQLITE_OK) {
    printf("\nCould not prepare statement.");
    return 1;
  }

  printf("\nThe statement has %d wildcards\n", sqlite3_bind_parameter_count(stmt));

  if (sqlite3_bind_double(
        stmt,
        1,  // Index of wildcard
        4.2
        )
      != SQLITE_OK) {
    printf("\nCould not bind double.\n");
    return 1;
  }

  if (sqlite3_bind_int(
        stmt,
        2,  // Index of wildcard
        42
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

  if (sqlite3_bind_null(
        stmt,
        1  // Index of wildcard
        )
      != SQLITE_OK) {
    printf("\nCould not bind double.\n");
    return 1;
  }

  if (sqlite3_bind_text (
        stmt,
        2,  // Index of wildcard
        "hello",
        5,  // length of text
        SQLITE_STATIC
        )
      != SQLITE_OK) {
    printf("\nCould not bind int.\n");
    return 1;
  }

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    printf("\nCould not step (execute) stmt.\n");
    return 1;
  }

  printf("\n");
  select_stmt("select * from foo");
  return 0;
}

////////////////////////////
static int count_callback(
	void *unnecessary_here,
	int number_of_columns_in_result_row, /* will always be 1 in this case */
	char **value_of_count, /* will be either 0 or 1 in this case */
	char **label_for_count) { /* will be COUNT(*) normally,
								 but modified via 'AS table_tablename' in this case*/
	printf("COUNT(*) %s\t=>\t%s\n", label_for_count[0], value_of_count[0] );
	return 0;
} // end of checkTable_Callback()


static int print_pragma()
{
	sqlite3_stmt *stmt;

	if ( sqlite3_prepare(
			 db, 
//			 "select count(*) from foo",  // stmt
			 "pragma cache_size",  // stmt
			 -1, // If than zero, then stmt is read up to the first nul terminator
			 &stmt,
			 0  // Pointer to unused portion of stmt
			 )
		 != SQLITE_OK) {
		printf("\nCould not prepare statement.");
		return 1;
	}

	while (true) {
		int ret = sqlite3_step(stmt);

		if (ret == SQLITE_BUSY) {
			continue;
		}
		else if (ret == SQLITE_DONE) {
			break;
		}
		else if (ret == SQLITE_ROW) {
			int num = sqlite3_column_int(stmt, 0);
			const unsigned char *name = sqlite3_column_text(stmt, 1);
			printf("NUM=%d, NAME=%s\n", num, name);
		}
	}

	// stmt を開放
	sqlite3_finalize(stmt);

	return 0;
}

static int set_pragma()
{
	sqlite3_stmt *stmt;
	int ret = 0;

	if ( ret = sqlite3_prepare(
			 db, 
#define USE_PLACE_HOLDER // XXX: near "?": syntax error in sqlite3_prepare
#ifdef USE_PLACE_HOLDER
//			 "insert into foo values (?,'xxx')",  // this stmt works fine
			 "pragma cache_size = ?",  // this stmt returns ERROR.
#else // USE_PLACE_HOLDER
			 "pragma cache_size = 200",  // stmt
#endif // USE_PLACE_HOLDER
			 -1, // If than zero, then stmt is read up to the first nul terminator
			 &stmt,
			 0  // Pointer to unused portion of stmt
			 )
		 != SQLITE_OK) {
		printf("\nCould not prepare statement. ret: %d\n", ret);
		printf("sqlite3_errmsg() %s\n", sqlite3_errmsg(db));
		return 1;
	}
#ifdef USE_PLACE_HOLDER
	if (sqlite3_bind_int(
			stmt,
			1,  // Index of wildcard
			100
			)
		!= SQLITE_OK) {
		printf("\nCould not bind int.\n");
		return 1;
	}
#endif // USE_PLACE_HOLDER

	while (true) {
		int ret = sqlite3_step(stmt);

		if (ret == SQLITE_BUSY) {
			continue;
		}
		else if (ret == SQLITE_DONE) {
			break;
		}
		else if (ret == SQLITE_ROW) {
			int num = sqlite3_column_int(stmt, 0);
			const unsigned char *name = sqlite3_column_text(stmt, 1);
			printf("NUM=%d, NAME=%s\n", num, name);
		}
	}

	// stmt を開放
	sqlite3_finalize(stmt);

	return 0;
}

int main() {
  sqlite3_open("./bind_insert_test.db", &db);

  if(db == 0) {
    printf("\nCould not open database.");
    return 1;
  }

  sql_stmt("create table foo (bar, baz)");


  int ret = insert_and_select();
  if (ret) {
	  printf("ret: %d\n", ret);
	  return ret;
  }

  print_pragma();
  set_pragma();
  print_pragma();

  sqlite3_close(db);
  return 0;
}
