NAME := bt_common

$(NAME)_MBINS_TYPE := kernel
$(NAME)_VERSION := 0.0.1
$(NAME)_SUMMARY := Common utilities used in BLE components.

$(NAME)_SOURCES-y := ./atomic_c.c \
                     ./buf.c \
                     ./log.c \
                     ./poll.c \
                     ./tinycrypt/source/cmac_mode.c \
                     ./tinycrypt/source/aes_encrypt.c \
                     ./rpa.c \
                     ./work.c \
                     ./tinycrypt/source/cmac_mode.c \
                     ./tinycrypt/source/aes_encrypt.c \
                     ./rpa.c \
                     ./work.c \
                     ./tinycrypt/source/utils.c \
                     ./tinycrypt/source/sha256.c \
                     ./tinycrypt/source/hmac.c \
                     ./tinycrypt/source/hmac_prng.c \
                     ./tinycrypt/source/cmac_mode.c \
                     ./tinycrypt/source/aes_encrypt.c \
                     ./tinycrypt/source/ecc.c \
                     ./tinycrypt/source/ecc_dh.c \
                     port/aos_port.c

$(NAME)_INCLUDES-y := ../../rhino/core/include \
                      ./include

GLOBAL_INCLUDES-y += ./include \
                     ./tinycrypt/include \
                     port/include
