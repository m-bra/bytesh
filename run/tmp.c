#include <fcntl.h>
#include <curl/curl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include <jansson.h>

#define NOSTRINGH
#define NOSTDIOH
#define NOUNISTDH
#include "main.h"

void replacebackslashesprecedingnlwithspace(char *dest, const char *src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (src[i] == '\\' && i + 1 < n && src[i+1] == 'n') {
            dest[i] = ' ';
            dest[i+1] = '\n';
        } else {
            dest[i] = src[i];
        }
    }
}

#define declbackslashtransformedcharbuf(new_name, orig_arr) \
    char new_name[sizeof(orig_arr)]; \
    replacebackslashesprecedingnlwithspace(new_name, orig_arr, sizeof(orig_arr))


/*struct membl {
    char *mem;
    size_t size;
};

// This function is called as soon as data arrives
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    slice_t *mem = (slice_t *)userp;

    // Append new data to our buffer
    char *pptr = realloc(mem->mem, mem->size + realsize + 1);
    if (!pptr) return 0; // Out of memory, aborts transfer

    mem->mem = pptr;
    memcpy(&(mem->mem[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->mem[mem->size] = 0;


    char *key_pos = strstr(mem->mem, "\"content\":");
    if (key_pos) {
    // Find the opening quote of the value string
    char *open_quote = strchr(key_pos + 10, '\"');
    if (open_quote) {
        char *pptr2 = open_quote + 1;

        // Iterate through the data to find the TRUE closing quote
        while (*pptr2 != '\0') {
            if (*pptr2 == '\"') {
                int backslashes = 0;
                char *back_ptr = pptr2 - 1;

                // Count consecutive backslashes immediately preceding this quote
                while (back_ptr >= open_quote + 1 && *back_ptr == '\\') {
                    backslashes++;
                    back_ptr--;
                }

                // If backslashes are even (0, 2, 4...), the quote is NOT escaped.
                if (backslashes % 2 == 0) {
                    // This is the real closing quote.
                    // Tell libcurl to kill the connection NOW.
                    return 0;
                }
                // If odd, it's an escaped quote (\"), so we keep looping.
            }
            pptr2++;
        }
    }
}
    
    return realsize;
}

char *llamacompleteone(char *prompt) {
    CURL *curl_handle;
    CURLcode res;
    slice_t chunk = {malloc(1), 0};

    char json_data[1024];
    snprintf(json_data, sizeof(json_data), "{\"prompt\": \"%s\", \"n_predict\": 1}", prompt);

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Connection: close");

    curl_easy_setopt(curl_handle, CURLOPT_URL, "http://127.0.0.1:8080/completion");
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, json_data);
    curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
    
    // Force IPv4 and disable keep-alive to be safe
    curl_easy_setopt(curl_handle, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl_handle, CURLOPT_TCP_KEEPALIVE, 0L);

    // This will return CURLE_WRITE_ERROR because we returned 0 in the callback
    res = curl_easy_perform(curl_handle);

    // Extraction logic (same as before)
   char *key_pos = strstr(chunk.mem, "\"content\":");
   char *start = 0; 
   if (key_pos) {
    // Find the opening quote of the value
    start = strchr(key_pos + 10, '\"');
    if (start) {
        start++; // Move to the first character inside the quotes
        char *pend = start;

        while (*pend != '\0') {
            if (*pend == '\"') {
                // Check for escaped quote by counting preceding backslashes
                int backslashes = 0;
                char *back_ptr = pend - 1;
                
                while (back_ptr >= start && *back_ptr == '\\') {
                    backslashes++;
                    back_ptr--;
                }

                // If backslashes are EVEN (0, 2, 4...), the quote is the REAL end.
                // If backslashes are ODD (1, 3, 5...), the quote is ESCAPED.
                if (backslashes % 2 == 0) {
                    break; 
                }
            }
            pend++;
        }

        if (*pend == '\"') {
            *pend = '\0'; // Terminate the string at the closing quote
            
            // return 0; // Returning 0 here tells libcurl to stop immediately
        }
    }
}
 
    // Cleanup
    curl_easy_cleanup(curl_handle);
    free(chunk.mem);
    curl_slist_free_all(headers);
    curl_global_cleanup();
   
    char *export = malloc(pagebuf_tn);
    memcpy(export, start, strlen(start));
    return export;
} 
*/

struct slice { char *mem; size_t size; };
typedef struct slice slice_t;

static int extend_buffer(slice_t *slice, void *src, size_t len) {
    char *pptr = realloc(slice->mem, slice->size + len + 1);
    if (!pptr) return 0;
    slice->mem = pptr;
    memcpy(&(slice->mem[slice->size]), src, len);
    slice->size += len;
    slice->mem[slice->size] = 0;
    return 1;
}

/*
static int is_unescaped_quote(char *p, char *start) {
    int backslashes = 0;
    char *back_ptr = p - 1;
    while (back_ptr >= start && *back_ptr == '\\') {
        backslashes++;
        back_ptr--;
    }
    return (backslashes % 2 == 0);
}

static int find_json_end(char *mem) {
    char *key = strstr(mem, "\"content\":");
    if (!key) return 1;
    char *open = strchr(key + 10, '\"');
    if (!open) return 1;
    for (char *p = open + 1; *p; p++) {
        if (*p == '\"' && is_unescaped_quote(p, open + 1)) return 0;
    }
    return 1;
}

void relay_unescaped(const char *mem) {
    static int esc = 0;
    for (size_t i = 0; mem[i]; i++) {
        if (!esc && mem[i] == '\\') { esc = 1; continue; }
        if (esc) {
            if (mem[i] == 'n') putchar('\n');
            else if (mem[i] == '\"') putchar('\"');
            else if (mem[i] == '\\') putchar('\\');
            else { putchar('\\'); putchar(mem[i]); }
            esc = 0;
        } else putchar(mem[i]);
    }
    fflush(stdout);
}

size_t write_callback(void *pptr, size_t size, size_t nmemb, void *userp) {
    size_t total = size * nmemb;
    slice_t *mem = (slice_t *)userp;
    if (!extend_buffer(mem, pptr, total)) return 0;
    return find_json_end(mem->mem) ? total : 0;
}

char* extract_content(char *mem) {
    char *key = strstr(mem, "\"content\":");
    if (!key) return NULL;
    char *start = strchr(key + 10, '\"');
    if (!start) return NULL;
    char *szend = ++start;
    while (*szend && (*szend != '\"' || !is_unescaped_quote(szend, start))) szend++;
    if (*szend == '\"') *szend = '\0';
    return start;
}

void setup_curl(CURL *h, char *json, slice_t *c, struct curl_slist *hd) {
    curl_easy_setopt(h, CURLOPT_URL, "http://127.0.0.1:8080/completion");
    curl_easy_setopt(h, CURLOPT_POSTFIELDS, json);
    curl_easy_setopt(h, CURLOPT_HTTPHEADER, hd);
    curl_easy_setopt(h, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(h, CURLOPT_WRITEDATA, (void *)c);
    curl_easy_setopt(h, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(h, CURLOPT_TCP_KEEPALIVE, 0L);
}

char *llamacompleteone(char *prompt) {
    slice_t chunk = {malloc(1), 0};
    char json[1024];
    snprintf(json, sizeof(json), "{\"prompt\": \"%s\", \"n_predict\": 1}", prompt);
    
    CURL *curl_handle = curl_easy_init();
    struct curl_slist *headers = curl_slist_append(NULL, "Content-Type: application/json");
    setup_curl(curl_handle, json, &chunk, headers);
    curl_easy_perform(curl_handle);
    char *raw = extract_content(chunk.mem);
    char *export = strdup(raw ? raw : ""); 
    curl_easy_cleanup(curl_handle);
    free(chunk.mem);
    curl_slist_free_all(headers);
    return export;
}

void llamacomplete(char *msg)
{
    setvbuf(getstdout(), NULL, _IONBF, 0);

    char text[pagebuf_tn];
    memcpy(text, msg, strlen(msg));
    struct pollfd pfd = {0, POLLIN, 0}; 
    rep 
    {
        char *newtext = llamacompleteone(text);

        / *
    char *src = newtext;
    char unescnewtext[strlen(text) + 1];
    memcpy(unescnewtext, src, strlen(newtext) + 1);
    char *dst = unescnewtext;

    while (*src) {
        if (*src == '\\' && *(src + 1) != '\0') {
            // Check the character after the backslash
            switch (*(src + 1)) {
                case 'n':  *dst++ = '\n'; src += 2; break;
                case '\"': *dst++ = '\"'; src += 2; break;
                case '\\': *dst++ = '\\'; src += 2; break;
                default:   *dst++ = *src++;         break; // Not a handled escape
            }
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0'; // Crucial: Terminate the now-shorter string)
* /
# define unescnewtext newtext
        relay_unescaped(unescnewtext); 
        memcpy(text + strlen(text), unescnewtext, strlen(unescnewtext)); 
        if (poll(&pfd, 1, 0) > 0 && getchar() == 'q') break;
        free(newtext);
    }
}*/

#include <stdio.h>
#include <curl/curl.h>





///

size_t grow_and_store(slice_t *m, void *p, size_t len) {
    char *pptr = realloc(m->mem, m->size + len + 1);
    if (!pptr) return 0;
    m->mem = pptr;
    memcpy(&(m->mem[m->size]), p, len);
    m->size += len;
    m->mem[m->size] = 0;
    return len;
}

void shift_buffer(slice_t *m, char *nl) {
    size_t off = (nl - m->mem) + 1;
    size_t rem = m->size - off;
    if (rem > 0) memmove(m->mem, m->mem + off, rem);
    m->size = rem;
    m->mem[m->size] = 0;
}

void print_content(char *p) {
    while (*p && *p != '\"') {
        if (*p == '\\' && *(p + 1) == 'n') { putchar('\n'); p += 2; }
        else if (*p == '\\' && *(p + 1) == '\"') { putchar('\"'); p += 2; }
        else { putchar(*p); p++; }
    }
    fflush(stdout);
}

void parse_chunk(const char *raw) {
    char *mem = strstr(raw, "data: ");
    if (!mem || strstr(mem, "[DONE]")) return;
    char *key = strstr(mem, "\"content\":");
    char *open = key ? strchr(key + 10, '\"') : NULL;
    if (open && (open - key < 15)) print_content(open + 1);
}

void process_lines(slice_t *m) {
    char *newline;
    while (m->mem && (newline = strchr(m->mem, '\n'))) {
        *newline = '\0'; // Temporarily terminate the string at the newline
        parse_chunk(m->mem);
        *newline = '\n'; // Restore it to calculate shift
        shift_buffer(m, newline);
    }
}

/*void process_buffer(slice_t *m) {
    char *nl;
    while (m->mem && (nl = strchr(m->mem, '\n'))) {
        size_t len = nl - m->mem;
        char *line = malloc(len + 1);
        if (!line) return;
        memcpy(line, m->mem, len);
        line[len] = '\0';
        //parse_chunk(line);
        printf("%s", line); 
        free(line);
        shift_buffer(m, nl);
    }
}*/

size_t stream_cb(void *p, size_t ss, size_t n, void *u) {
    slice_t *m = (slice_t *)u;
    size_t total = ss * n;
    
    //printf("\n[DEBUG] PACKET START (%zu bytes)\n", total);
    //printf("%.*s", (int)total, (char *)p);
    //printf("\n[DEBUG] PACKET END\n");

    if (!extend_buffer(m, p, total)) return 0;
    process_lines(m);
    return total;
}

struct curl_slist* get_hdls() {
    struct curl_slist *h = NULL;
    return curl_slist_append(h, "Content-Type: application/json");
}

void set_opts(CURL *c, char *json, struct curl_slist *h) {
    curl_easy_setopt(c, CURLOPT_URL, "http://127.0.0.1:8080/v1/chat/completions");
    curl_easy_setopt(c, CURLOPT_POSTFIELDS, json);
    curl_easy_setopt(c, CURLOPT_HTTPHEADER, h);
    curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, stream_cb);
}

void execute_request(slice_t *m, char *json) {
    CURL *c = curl_easy_init();
    struct curl_slist *h = get_hdls();
    curl_easy_setopt(c, CURLOPT_WRITEDATA, m);
    set_opts(c, json, h);
    curl_easy_perform(c);
    curl_slist_free_all(h);
    curl_easy_cleanup(c);
}

char* build_payload(const char *prompt) {
    json_t *root;
    json_error_t error;

    // "s" = string, "b" = boolean, "[]" = array, "{}" = object
    root = json_pack("{s:[{s:s, s:s}], s:b}", 
                     "messages", 
                        "role", "user", 
                        "content", prompt, 
                     "stream", 1);

    if (!root) {
        fprintf(stderr, "JSON Pack Error: %s\n", error.text);
        return NULL;
    }

    // JSON_COMPACT creates a single-line string without extra spaces
    char *payload = json_dumps(root, JSON_COMPACT);
    
    json_decref(root); // Free the JSON object memory
    return payload;    // Note: Caller must free() this string!
}

void llamacomplete(char *rawmsg) {
    char *msg = build_payload(rawmsg);
    slice_t m = {malloc(1), 0};
    if (!m.mem) return;
    m.mem[0] = 0;
    execute_request(&m, msg);
    if (m.size > 0) parse_chunk(m.mem); 
    free(m.mem);
    free(msg);
}


__attribute__((noinline, used))
void llamacompleteold(char *msg)
{
    #define ASSERT_LOCAL_PAGEBUF_IS_ARRAY
    char pagebuf[pagebuf_tn * 16];
    *stpncpy(pagebuf, msg, sizeof(pagebuf)) = '\0';
    for (int k = 0; k < 3; ++k)
    {
        __asm__ volatile ("" : : "m" (k)); // "m" forces k into a memory location
printf("DBG[A]\n");
        char prevpagebuf[sizeof(pagebuf)];
        memcpy(prevpagebuf, pagebuf, sizeof(pagebuf));
        pagebuf[0] = '\0';
        popenrcollect(mf(
            "strace -r wget "
              "--post-data='{%c%s%c: %c%s%c, %c%s%c: %d}' "
              "--header=%c%s%c "
              "http://localhost:8080/completion -O -", 
            '"', "prompt", '"', '"', prevpagebuf, '"',
            '"', "n_predict", '"', 2,
            '"', "Content-Type: application/json", '"')

        /*      "curl -v --no-keepalive -0 -4 -sS -H \"Expect:\" -N -H \"Connection: close\" --request POST "\
                "--url http://127.0.0.1:8080/completion "\
                "--header "\
                    "\"Content-Type: application/json\" "\
                "--data '{"\
                    "\"prompt\": \"%s\", "\
                    "\"n_predict\": 8}' "
                    ,
            prevpagebuf)*/, pagebuf, 
            sizeof(pagebuf) ASSERT_LOCAL_PAGEBUF_IS_ARRAY 
                - strlen(pagebuf));
printf("DBG[B]\n");
        if (strlen(prevpagebuf) + strlen(pagebuf) + 1 > sizeof(prevpagebuf))
            printf("Warning: We are currently corrupting working memory at %s:%d\n", __FILE__, __LINE__);
        declbackslashtransformedcharbuf(transfpagebuf, pagebuf);
        printf("%s ", transfpagebuf); 
        fflush(getstdout());
        fsync(fileno(getstdout()));
        memcpy(prevpagebuf + strlen(prevpagebuf), pagebuf, strlen(pagebuf));
        memcpy(pagebuf, prevpagebuf, sizeof(pagebuf));
        pagebuf[strlen(pagebuf) + 1] = '\0';
        pagebuf[strlen(pagebuf)] = ' ';
    }
    printf("CHILD PROCESS EXITED\n");
}

