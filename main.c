#include <stdio.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>

void printODBCError(SQLHANDLE handle, SQLSMALLINT handleType, SQLRETURN ret)
{
    SQLCHAR SQLState[6], message[SQL_MAX_MESSAGE_LENGTH];
    SQLINTEGER nativeError;
    SQLSMALLINT i, messageLength;

    if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, &nativeError, message, sizeof(message), &messageLength))
    {
        printf("ODBC Error: %s - %s\n", SQLState, message);
    }
}

int main()
{
    SQLHENV env;
    SQLHDBC dbc;
    SQLRETURN ret;

    // Inicializar el entorno
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        printf("Error al inicializar el entorno\n");
        return 1;
    }

    ret = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        printf("Error al configurar la versión de ODBC\n");
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        return 1;
    }

    // Inicializar la conexión
    ret = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        printf("Error al inicializar la conexión\n");
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        return 1;
    }

    ret = SQLDriverConnect(dbc, NULL, (SQLCHAR *)"DRIVER={SQL Server};SERVER=568e70c42d9f;DATABASE=diccionario;UID=sa;PWD=Pi3141592654!;", SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        printf("Error al conectar a la base de datos\n");
        printODBCError(dbc, SQL_HANDLE_DBC, ret);
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        return 1;
    }

    int numero = 123;
    char texto[] = "ejemplo_texto";

    SQLCHAR *insertQuery = (SQLCHAR *)"INSERT INTO Ejemplo (Numero, Texto) VALUES (?, ?);";
    SQLINTEGER numeroValue = numero;
    SQLLEN numeroValueLen = sizeof(numeroValue);
    SQLCHAR *textoValue = texto;
    SQLLEN textoValueLen = SQL_NTS;

    SQLHSTMT stmt;
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        printf("Error al inicializar la declaración\n");
        printODBCError(dbc, SQL_HANDLE_DBC, ret);
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        return 1;
    }

    ret = SQLPrepare(stmt, insertQuery, SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        printf("Error al preparar la declaración\n");
        printODBCError(stmt, SQL_HANDLE_STMT, ret);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        return 1;
    }

    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &numeroValue, 0, &numeroValueLen);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        printf("Error al enlazar el parámetro 1\n");
        printODBCError(stmt, SQL_HANDLE_STMT, ret);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        return 1;
    }

    ret = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(texto), 0, textoValue, sizeof(texto), &textoValueLen);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        printf("Error al enlazar el parámetro 2\n");
        printODBCError(stmt, SQL_HANDLE_STMT, ret);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        return 1;
    }

    ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        printf("Error al ejecutar la declaración\n");
        printODBCError(stmt, SQL_HANDLE_STMT, ret);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        return 1;
    }

    printf("La inserción se realizó correctamente\n");

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);

    return 0;
}
