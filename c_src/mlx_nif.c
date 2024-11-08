#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <erl_nif.h>

static ERL_NIF_TERM am_ok;
static ERL_NIF_TERM am_error;
static ERL_NIF_TERM am_badarg;

static int
on_load(ErlNifEnv *env, void **priv, ERL_NIF_TERM info)
{
    am_ok = enif_make_atom(env, "ok");
    am_error = enif_make_atom(env, "error");
    am_error = enif_make_atom(env, "badarg");

    return 0;
}

static ERL_NIF_TERM
make_binary(ErlNifEnv *env, const char *bytes, size_t size)
{
    ERL_NIF_TERM bin;
    uint8_t *data = enif_make_new_binary(env, size, &bin);
    memcpy(data, bytes, size);
    return bin;
}

static ERL_NIF_TERM
make_badarg(ErlNifEnv *env, ERL_NIF_TERM arg)
{
    ERL_NIF_TERM badarg = enif_make_tuple2(env, am_badarg, arg);
    return enif_raise_exception(env, badarg);
}

static ERL_NIF_TERM
library_version(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
    const char *version = "v0.18.0";
    return make_binary(env, version, strlen(version));
}

static ErlNifFunc nif_funcs[] = {
    {"library_version", 0, library_version, 0},
};

ERL_NIF_INIT(Elixir.MLX, nif_funcs, on_load, NULL, NULL, NULL)
