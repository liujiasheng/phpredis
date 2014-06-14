#ifndef REDIS_LIBRARY_H
#define REDIS_LIBRARY_H

void add_constant_long(zend_class_entry *ce, char *name, int value);
int integer_length(int i);
int redis_cmd_format(char **ret, char *format, ...);
int redis_cmd_format_static(char **ret, char *keyword, char *format, ...);
int redis_cmd_format_header(char **ret, char *keyword, int arg_count);
int redis_cmd_append_str(char **cmd, int cmd_len, char *append, int append_len);
int redis_cmd_init_sstr(smart_str *str, int num_args, char *keyword, int keyword_len);
int redis_cmd_append_sstr(smart_str *str, char *append, int append_len);
int redis_cmd_append_sstr_int(smart_str *str, int append);
int redis_cmd_append_sstr_long(smart_str *str, long append);
int redis_cmd_append_int(char **cmd, int cmd_len, int append);
int redis_cmd_append_sstr_dbl(smart_str *str, double value);

PHP_REDIS_API char* redis_sock_read(RedisSock *redis_sock, int *buf_len TSRMLS_DC);
PHP_REDIS_API void redis_1_response(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock, zval *z_tab, void *ctx);
PHP_REDIS_API void redis_long_response(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock, zval* z_tab, void *ctx);
PHP_REDIS_API char* redis_sock_read(RedisSock *redis_sock, int *buf_len TSRMLS_DC);
PHP_REDIS_API int redis_sock_gets(RedisSock *redis_sock, char *buf, int buf_size, size_t* line_len TSRMLS_DC);

typedef void (*SuccessCallback)(RedisSock *redis_sock);

PHPAPI int redis_subscribe_response(INTERNAL_FUNCTION_PARAMETERS, 
        RedisSock *redis_sock, zval *z_tab, void *ctx);

PHPAPI int redis_sock_write(RedisSock *redis_sock, char *cmd, size_t sz TSRMLS_DC);
PHPAPI void redis_stream_close(RedisSock *redis_sock TSRMLS_DC);
PHPAPI int redis_check_eof(RedisSock *redis_sock TSRMLS_DC);
PHPAPI int redis_sock_get(zval *id, RedisSock **redis_sock TSRMLS_DC, int nothrow);
PHPAPI void redis_free_socket(RedisSock *redis_sock);
PHPAPI void redis_send_discard(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock);
PHPAPI int redis_sock_set_err(RedisSock *redis_sock, const char *msg, int msg_len);

PHP_REDIS_API void redis_mbulk_reply_loop(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock, zval *z_tab, int count, int unserialize);
PHP_REDIS_API int redis_mbulk_reply_raw(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock, zval *z_tab, void *ctx);
PHP_REDIS_API int redis_mbulk_reply_zipped_raw(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock, zval *z_tab, void *ctx);
PHP_REDIS_API int redis_mbulk_reply_zipped_vals(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock, zval *z_tab, void *ctx);
PHP_REDIS_API int redis_mbulk_reply_zipped_keys_int(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock, zval *z_tab, void *ctx);
PHP_REDIS_API int redis_mbulk_reply_zipped_keys_dbl(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock, zval *z_tab, void *ctx);
PHP_REDIS_API int redis_mbulk_reply_assoc(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock, zval *z_tab, void *ctx);

PHP_REDIS_API int redis_sock_read_scan_reply(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock, REDIS_SCAN_TYPE type, long *iter);
PHP_REDIS_API int redis_sock_write(RedisSock *redis_sock, char *cmd, size_t sz TSRMLS_DC);
PHP_REDIS_API void redis_stream_close(RedisSock *redis_sock TSRMLS_DC);
PHP_REDIS_API int redis_check_eof(RedisSock *redis_sock TSRMLS_DC);
/*PHP_REDIS_API int redis_sock_get(zval *id, RedisSock **redis_sock TSRMLS_DC);*/
PHP_REDIS_API void redis_free_socket(RedisSock *redis_sock);
PHP_REDIS_API void redis_send_discard(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock);
PHP_REDIS_API int redis_sock_set_err(RedisSock *redis_sock, const char *msg, int msg_len);

PHP_REDIS_API int redis_sock_write(RedisSock *redis_sock, char *cmd, size_t sz TSRMLS_DC);
PHP_REDIS_API void redis_stream_close(RedisSock *redis_sock TSRMLS_DC);
PHP_REDIS_API int redis_check_eof(RedisSock *redis_sock TSRMLS_DC);
/* PHP_REDIS_API int redis_sock_get(zval *id, RedisSock **redis_sock TSRMLS_DC); */
PHP_REDIS_API void redis_free_socket(RedisSock *redis_sock);
PHP_REDIS_API void redis_send_discard(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock);
PHP_REDIS_API int redis_sock_set_err(RedisSock *redis_sock, const char *msg, int msg_len);

PHP_REDIS_API int redis_serialize(int serializer, zval *z, char **val, int *val_len TSRMLS_DC);
PHP_REDIS_API int redis_unserialize(int serializer, const char *val, int val_len, zval **return_value TSRMLS_DC);
PHP_REDIS_API int redis_key_prefix(RedisSock *redis_sock, char **key, int *key_len TSRMLS_DC);


/*
* Variant Read methods, mostly to implement eval
*/

PHP_REDIS_API int redis_read_reply_type(RedisSock *redis_sock, REDIS_REPLY_TYPE *reply_type, int *reply_info TSRMLS_DC);
PHP_REDIS_API int redis_read_variant_line(RedisSock *redis_sock, REDIS_REPLY_TYPE reply_type, zval **z_ret TSRMLS_DC);
PHP_REDIS_API int redis_read_variant_bulk(RedisSock *redis_sock, int size, zval **z_ret TSRMLS_DC);
PHP_REDIS_API int redis_read_multibulk_recursive(RedisSock *redis_sock, int elements, zval **z_ret TSRMLS_DC);
PHP_REDIS_API int redis_read_variant_reply(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock, zval *z_tab);

PHP_REDIS_API void redis_client_list_reply(INTERNAL_FUNCTION_PARAMETERS, RedisSock *redis_sock, zval *z_tab);

#if ZEND_MODULE_API_NO >= 20100000
#define REDIS_DOUBLE_TO_STRING(dbl_str, dbl_len, dbl) do { \
	char dbl_decsep; \
	dbl_decsep = '.'; \
    dbl_str = _php_math_number_format_ex(dbl, 16, &dbl_decsep, 1, NULL, 0); \
	dbl_len = strlen(dbl_str); \
	} while (0);
#else
#define REDIS_DOUBLE_TO_STRING(dbl_str, dbl_len, dbl) \
	dbl_str = _php_math_number_format(dbl, 16, '.', '\x00'); \
	dbl_len = strlen(dbl_str);
#endif

#endif
