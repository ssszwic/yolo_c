ROOT_DIR = /SSD/szw/Work/yolo_c
INCLUDE_DIR = $(ROOT_DIR)/include
BUILD_DIR = $(ROOT_DIR)/build
SRC_DIR = $(ROOT_DIR)/src
TARGET = $(BUILD_DIR)/yolo_c

SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:.c=.o)))

CFLAGS += -I $(INCLUDE_DIR)

compile: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.d : $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@set -e; \
	gcc -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\$(BUILD_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(OBJS:.o=.d)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

run:
	$(TARGET)

clean:
	-rm -r $(BUILD_DIR)
