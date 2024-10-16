/*
 * PgBouncer - Lightweight connection pooler for PostgreSQL.
 *
 * Copyright (c) 2007-2009  Marko Kreen, Skype Technologies OÜ
 * Copyright (c) 2022 Cloudflare, Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

static inline int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

static inline int max(int a, int b)
{
     if (a > b)
        return a;
    return b;
}

bool server_proto(SBuf *sbuf, SBufEvent evtype, struct MBuf *pkt)  _MUSTCHECK;
void kill_pool_logins(PgPool *pool, const char *msg);
int pool_pool_mode(PgPool *pool) _MUSTCHECK;
int pool_pool_size(PgPool *pool) _MUSTCHECK;
int pool_min_pool_size(PgPool *pool) _MUSTCHECK;
int pool_res_pool_size(PgPool *pool) _MUSTCHECK;
int database_max_connections(PgDatabase *db) _MUSTCHECK;
void database_add_user_password(PgDatabase *db, const char *username, const char *passwd);
int user_max_connections(PgUser *user) _MUSTCHECK;
bool user_requires_auth_query(PgUser *user) _MUSTCHECK;
int user_passwd_node_cmp(uintptr_t user_passwd_ptr, struct AANode *node) _MUSTCHECK;
void user_passwd_free(struct AANode *node, void *arg);
char *user_password(PgUser *user, PgDatabase *db) _MUSTCHECK;
