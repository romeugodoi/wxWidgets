#ifndef _INTRINSIC_SQLEXT_H
# define _INTRINSIC_SQLEXT_H

# include       <isql.h>

# define SQL_STILL_EXECUTING            2
# define SQL_NEED_DATA                  99

/* extend SQL datatypes */
# define SQL_DATE                       9
# define SQL_TIME                       10
# define SQL_TIMESTAMP                  11
# define SQL_LONGVARCHAR                (-1)
# define SQL_BINARY                     (-2)
# define SQL_VARBINARY                  (-3)
# define SQL_LONGVARBINARY              (-4)
# define SQL_BIGINT                     (-5)
# define SQL_TINYINT                    (-6)
# define SQL_BIT                        (-7)    /* conflict with SQL3 ??? */
# define SQL_TYPE_DRIVER_START          (-80)

/* C to SQL datatype mapping */
# define SQL_C_DATE                     SQL_DATE
# define SQL_C_TIME                     SQL_TIME
# define SQL_C_TIMESTAMP                SQL_TIMESTAMP
# define SQL_C_BINARY                   SQL_BINARY
# define SQL_C_BIT                      SQL_BIT
# define SQL_C_TINYINT                  SQL_TINYINT

# define SQL_SIGNED_OFFSET              (-20)
# define SQL_UNSIGNED_OFFSET            (-22)

# define SQL_C_SLONG                    (SQL_C_LONG  + SQL_SIGNED_OFFSET)
# define SQL_C_SSHORT                   (SQL_C_SHORT + SQL_SIGNED_OFFSET)
# define SQL_C_STINYINT                 (SQL_TINYINT + SQL_SIGNED_OFFSET)
# define SQL_C_ULONG                    (SQL_C_LONG  + SQL_UNSIGNED_OFFSET)
# define SQL_C_USHORT                   (SQL_C_SHORT + SQL_UNSIGNED_OFFSET)
# define SQL_C_UTINYINT                 (SQL_TINYINT + SQL_UNSIGNED_OFFSET)
# define SQL_C_BOOKMARK                 SQL_C_ULONG

# if defined(SQL_TYPE_MIN)
#   undef  SQL_TYPE_MIN
#   define SQL_TYPE_MIN                 SQL_BIT
/* Note:If SQL_BIT uses SQL3 value (i.e. 14) then,
 *      SQL_TYPE_MIN need to be defined as SQL_TINYINT
 *      (i.e. -6).
 */
# endif

# define SQL_ALL_TYPES                  0

/* SQLDriverConnect flag values */
# define SQL_DRIVER_NOPROMPT            0
# define SQL_DRIVER_COMPLETE            1
# define SQL_DRIVER_PROMPT              2
# define SQL_DRIVER_COMPLETE_REQUIRED   3

/* SQLSetParam extensions */
# define SQL_DEFAULT_PARAM              (-5)
# define SQL_IGNORE                     (-6)

/* function number for SQLGetFunctions and _iodbcdm_getproc */
# define SQL_API_SQLALLOCCONNECT        1
# define SQL_API_SQLALLOCENV            2
# define SQL_API_SQLALLOCSTMT           3
# define SQL_API_SQLBINDCOL             4
# define SQL_API_SQLCANCEL              5
# define SQL_API_SQLCOLATTRIBUTES       6
# define SQL_API_SQLCONNECT             7
# define SQL_API_SQLDESCRIBECOL         8
# define SQL_API_SQLDISCONNECT          9
# define SQL_API_SQLERROR               10
# define SQL_API_SQLEXECDIRECT          11
# define SQL_API_SQLEXECUTE             12
# define SQL_API_SQLFETCH               13
# define SQL_API_SQLFREECONNECT         14
# define SQL_API_SQLFREEENV             15
# define SQL_API_SQLFREESTMT            16
# define SQL_API_SQLGETCURSORNAME       17
# define SQL_API_SQLNUMRESULTCOLS       18
# define SQL_API_SQLPREPARE             19
# define SQL_API_SQLROWCOUNT            20
# define SQL_API_SQLSETCURSORNAME       21
# define SQL_API_SQLSETPARAM            22
# define SQL_API_SQLTRANSACT            23

# define SQL_NUM_FUNCTIONS              23

# define SQL_EXT_API_START              40

# define SQL_API_SQLCOLUMNS             40

# define SQL_API_SQLDRIVERCONNECT       41
# define SQL_API_SQLGETCONNECTOPTION    42
# define SQL_API_SQLGETDATA             43
# define SQL_API_SQLGETFUNCTIONS        44
# define SQL_API_SQLGETINFO             45
# define SQL_API_SQLGETSTMTOPTION       46
# define SQL_API_SQLGETTYPEINFO         47
# define SQL_API_SQLPARAMDATA           48
# define SQL_API_SQLPUTDATA             49
# define SQL_API_SQLSETCONNECTOPTION    50
# define SQL_API_SQLSETSTMTOPTION       51
# define SQL_API_SQLSPECIALCOLUMNS      52
# define SQL_API_SQLSTATISTICS          53
# define SQL_API_SQLTABLES              54

# define SQL_API_SQLBROWSECONNECT       55
# define SQL_API_SQLCOLUMNPRIVILEGES    56
# define SQL_API_SQLDATASOURCES         57
# define SQL_API_SQLDESCRIBEPARAM       58
# define SQL_API_SQLEXTENDEDFETCH       59
# define SQL_API_SQLFOREIGNKEYS         60
# define SQL_API_SQLMORERESULTS         61
# define SQL_API_SQLNATIVESQL           62
# define SQL_API_SQLNUMPARAMS           63
# define SQL_API_SQLPARAMOPTIONS        64
# define SQL_API_SQLPRIMARYKEYS         65
# define SQL_API_SQLPROCEDURECOLUMNS    66
# define SQL_API_SQLPROCEDURES          67
# define SQL_API_SQLSETPOS              68
# define SQL_API_SQLSETSCROLLOPTIONS    69
# define SQL_API_SQLTABLEPRIVILEGES     70

# define SQL_API_SQLDRIVERS             71
# define SQL_API_SQLBINDPARAMETER       72
# define SQL_EXT_API_LAST               SQL_API_SQLBINDPARAMETER

# define SQL_API_ALL_FUNCTIONS          0

/* SQLGetInfo infor number */
# define SQL_INFO_FIRST                 0
# define SQL_DRIVER_HDBC                3
# define SQL_DRIVER_HENV                4
# define SQL_DRIVER_HSTMT               5
# define SQL_DRIVER_NAME                6
# define SQL_ODBC_VER                   10
# define SQL_CURSOR_COMMIT_BEHAVIOR     23
# define SQL_CURSOR_ROLLBACK_BEHAVIOR   24
# define SQL_DEFAULT_TXN_ISOLATION      26

# define SQL_TXN_ISOLATION_OPTION       72
# define SQL_NON_NULLABLE_COLUMNS       75

# define SQL_DRIVER_HLIB                76
# define SQL_DRIVER_ODBC_VER            77

# define SQL_QUALIFIER_LOCATION         114

# define SQL_INFO_LAST                  SQL_QUALIFIER_LOCATION

# define SQL_INFO_DRIVER_START          1000


/* SQL_TXN_ISOLATION_OPTION masks */
# define SQL_TXN_READ_UNCOMMITTED       0x00000001L
# define SQL_TXN_READ_COMMITTED         0x00000002L
# define SQL_TXN_REPEATABLE_READ        0x00000004L
# define SQL_TXN_SERIALIZABLE           0x00000008L
# define SQL_TXN_VERSIONING             0x00000010L

/* SQL_CURSOR_COMMIT_BEHAVIOR and SQL_CURSOR_ROLLBACK_BEHAVIOR values */

# define SQL_CB_DELETE                  0x0000
# define SQL_CB_CLOSE                   0x0001
# define SQL_CB_PRESERVE                0x0002

/* options for SQLGetStmtOption/SQLSetStmtOption */
# define SQL_QUERY_TIMEOUT              0
# define SQL_MAX_ROWS                   1
# define SQL_NOSCAN                     2
# define SQL_MAX_LENGTH                 3
# define SQL_ASYNC_ENABLE               4
# define SQL_BIND_TYPE                  5
# define SQL_CURSOR_TYPE                6
# define SQL_CONCURRENCY                7
# define SQL_KEYSET_SIZE                8
# define SQL_ROWSET_SIZE                9
# define SQL_SIMULATE_CURSOR            10
# define SQL_RETRIEVE_DATA              11
# define SQL_USE_BOOKMARKS              12
# define SQL_GET_BOOKMARK               13      /* GetStmtOption Only */
# define SQL_ROW_NUMBER                 14      /* GetStmtOption Only */
# define SQL_STMT_OPT_MAX               SQL_ROW_NUMBER

# define SQL_STMT_OPT_MIN               SQL_QUERY_TIMEOUT


/* SQL_QUERY_TIMEOUT options */
# define SQL_QUERY_TIMEOUT_DEFAULT      0UL

/* SQL_MAX_ROWS options */
# define SQL_MAX_ROWS_DEFAULT           0UL

/* SQL_MAX_LENGTH options */
# define SQL_MAX_LENGTH_DEFAULT         0UL

/* SQL_CONCURRENCY options */
# define SQL_CONCUR_READ_ONLY           1
# define SQL_CONCUR_LOCK                2
# define SQL_CONCUR_ROWVER              3
# define SQL_CONCUR_VALUES              4

/* SQL_CURSOR_TYPE options */
#define SQL_CURSOR_FORWARD_ONLY		0UL
#define SQL_CURSOR_KEYSET_DRIVEN	1UL
#define SQL_CURSOR_DYNAMIC		2UL
#define SQL_CURSOR_STATIC               3UL
#define SQL_CURSOR_TYPE_DEFAULT		SQL_CURSOR_FORWARD_ONLY

/* options for SQLSetConnectOption/SQLGetConnectOption */
# define SQL_ACCESS_MODE                101
# define SQL_AUTOCOMMIT                 102
# define SQL_LOGIN_TIMEOUT              103
# define SQL_OPT_TRACE                  104
# define SQL_OPT_TRACEFILE              105
# define SQL_TRANSLATE_DLL              106
# define SQL_TRANSLATE_OPTION           107
# define SQL_TXN_ISOLATION              108
# define SQL_CURRENT_QUALIFIER          109
# define SQL_ODBC_CURSORS               110
# define SQL_QUIET_MODE                 111
# define SQL_PACKET_SIZE                112
# define SQL_CONN_OPT_MAX               SQL_PACKET_SIZE
# define SQL_CONNECT_OPT_DRVR_START     1000

# define SQL_CONN_OPT_MIN               SQL_ACCESS_MODE

/* SQL_ACCESS_MODE options */
# define SQL_MODE_READ_WRITE            0UL
# define SQL_MODE_READ_ONLY             1UL
# define SQL_MODE_DEFAULT               SQL_MODE_READ_WRITE

/* SQL_AUTOCOMMIT options */
# define SQL_AUTOCOMMIT_OFF             0UL
# define SQL_AUTOCOMMIT_ON              1UL
# define SQL_AUTOCOMMIT_DEFAULT         SQL_AUTOCOMMIT_ON

/* SQL_LOGIN_TIMEOUT options */
# define SQL_LOGIN_TIMEOUT_DEFAULT      15UL

/* SQL_OPT_TRACE options */
# define SQL_OPT_TRACE_OFF              0UL
# define SQL_OPT_TRACE_ON               1UL
# define SQL_OPT_TRACE_DEFAULT          SQL_OPT_TRACE_OFF
# define SQL_OPT_TRACE_FILE_DEFAULT     "odbc.log"

/* SQL_ODBC_CURSORS options */
# define SQL_CUR_USE_IF_NEEDED          0UL
# define SQL_CUR_USE_ODBC               1UL
# define SQL_CUR_USE_DRIVER             2UL
# define SQL_CUR_DEFAULT                SQL_CUR_USE_DRIVER

/* Column types and scopes in SQLSpecialColumns. */
# define SQL_BEST_ROWID                 1
# define SQL_ROWVER                     2

# define SQL_SCOPE_CURROW               0
# define SQL_SCOPE_TRANSACTION          1
# define SQL_SCOPE_SESSION              2

/* Operations in SQLSetPos */
# define SQL_ADD                        4

/* Lock options in SQLSetPos */
# define SQL_LOCK_NO_CHANGE             0
# define SQL_LOCK_EXCLUSIVE             1
# define SQL_LOCK_UNLOCK                2

/* SQLExtendedFetch flag values */
# define SQL_FETCH_NEXT                 1
# define SQL_FETCH_FIRST                2
# define SQL_FETCH_LAST                 3
# define SQL_FETCH_PRIOR                4
# define SQL_FETCH_ABSOLUTE             5
# define SQL_FETCH_RELATIVE             6
# define SQL_FETCH_BOOKMARK             8

/* Defines for SQLBindParameter/SQLProcedureColumns */
# define SQL_PARAM_TYPE_UNKNOWN         0
# define SQL_PARAM_INPUT                1
# define SQL_PARAM_INPUT_OUTPUT         2
# define SQL_RESULT_COL                 3
# define SQL_PARAM_OUTPUT               4

/* Defines used by Driver Manager for mapping SQLSetParam to SQLBindParameter */
# define SQL_PARAM_TYPE_DEFAULT         SQL_PARAM_INPUT_OUTPUT
# define SQL_SETPARAM_VALUE_MAX         (-1L)

/* SQLStatistics flag values */
# define SQL_INDEX_UNIQUE               0
# define SQL_INDEX_ALL                  1

# define SQL_QUICK                      0
# define SQL_ENSURE                     1

/* SQLSetScrollOption flag values */
# define SQL_SCROLL_FORWARD_ONLY        0L
# define SQL_SCROLL_KEYSET_DRIVEN       (-1L)
# define SQL_SCROLL_DYNAMIC             (-2L)
# define SQL_SCROLL_STATIC              (-3L)

# if defined(__cplusplus) || defined(__IBMCPP__)
        extern  "C" {
# endif

RETCODE SQL_API SQLSetConnectOption (HDBC, UWORD, UDWORD);
RETCODE SQL_API SQLNumResultCols ( HSTMT, SWORD FAR* );

# if defined(__cplusplus) || defined(__IBMCPP__)
        }
# endif

#endif
