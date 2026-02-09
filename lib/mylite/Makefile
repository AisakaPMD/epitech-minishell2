##
## EPITECH PROJECT, 2025
## My Lib and My Printf merge
## File description:
## Main makefile
##

SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin
INCLUDE_DIR := include

NAME := $(BIN_DIR)/libmy.a
SRC_FILES := my_printf.c printf_utils.c printf_utils_strbuf.c \
	printf_utils_str.c printf_utils_misc.c \
	printf_utils_float.c printf_utils_nbr.c \
	printf_specifier_g.c printf_specifier_x.c \
	printf_specifier_e.c printf_specifier_a.c \
	printf_specifier_b.c printf_specifier_c.c \
	printf_specifier_u.c printf_specifier_s.c \
	printf_specifier_o.c printf_specifier_p.c \
	printf_specifier_n.c printf_specifier_m.c \
	printf_specifier_di.c printf_specifier_f.c \
	printf_main_dprintf.c printf_main_vdprintf.c \
	printf_main_fprintf.c printf_main_vfprintf.c \
	printf_main_sprintf.c printf_main_vsprintf.c \
	printf_main_snprintf.c printf_main_vsnprintf.c \
	printf_main_printf.c printf_main_vprintf.c \
	math_utils.c nbr_utils.c pointer_utils.c str_utils.c \
	str_utils_2.c str_utils_3.c str_utils_4.c misc_utils.c \
	str_checks.c ll_adders.c ll_removers.c ll_utils.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) | $(BIN_DIR)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $< -o $@ -I$(INCLUDE_DIR)

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) *.gcda *.gcno *.gcov *.gcov.json.gz *.profraw

fclean: clean
	rm -fr $(OBJ_DIR) $(BIN_DIR) $(TEST_NAME)

re: fclean all
