CC = gcc
AR = ar rcs

TARGET = cuat.a
CFLAGS = -I$(INCLUDE_DIR) $(foreach dependencies,$(DEPENDENCIES),-I$(dependencies)/include)

INCLUDE_DIR = includes
SRC_DIR = src
OBJ_DIR = obj
DEPENDENCIES =

SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEPENDENCIES_OBJ = $(shell find $(DEPENDENCIES) -name '*.o')

all: build_dependencies $(TARGET)

build_dependencies:
	@$(foreach dependencies, $(DEPENDENCIES), make -C $(dependencies);)

$(TARGET): $(OBJ)
	@echo "Lib '$(TARGET)' successfully build"
	$(AR) $(TARGET) $(OBJ) $(DEPENDENCIES_OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "making directory '$(OBJ_DIR)' since it doesn't exist"

clean:
	@$(foreach dependencies, $(DEPENDENCIES), make -C $(dependencies) clean;)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(foreach dependencies, $(DEPENDENCIES), make -C $(dependencies) fclean;)
	@rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re