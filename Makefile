# ReadyTasks standalone build for C64/cc65

CC = cl65
C1541 = c1541

SRC_DIR = src
LIB_DIR = $(SRC_DIR)/lib
OBJ_DIR = obj

APP = readytasks.prg
DISK = readytasks.d64
DISK_README = disk/readme.seq
MAP = $(OBJ_DIR)/readytasks.map

# Standard C64 target: produces a regular BASIC-runnable PRG (LOAD+RUN)
CFLAGS = -t c64 -I$(SRC_DIR)

TUI_SRCS = \
	$(LIB_DIR)/tui_core.c \
	$(LIB_DIR)/tui_window.c \
	$(LIB_DIR)/tui_menu.c \
	$(LIB_DIR)/tui_input.c \
	$(LIB_DIR)/tui_misc.c

SRCS = \
	$(SRC_DIR)/readytasks.c \
	$(LIB_DIR)/clipboard_local.c \
	$(TUI_SRCS)

all: $(APP)

$(APP): $(SRCS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -m $(MAP) -o $@ $(SRCS)

$(DISK): $(APP) $(DISK_README) scripts/make_d64.sh
	./scripts/make_d64.sh $(APP) $(DISK) $(DISK_README)

d64: $(DISK)

run: d64 scripts/run_vice.sh
	./scripts/run_vice.sh $(DISK) $(APP)

run-console: d64 scripts/run_vice.sh
	VICE_CONSOLE=1 ./scripts/run_vice.sh $(DISK) $(APP)

clean:
	rm -f $(APP) $(DISK) $(SRC_DIR)/*.o $(LIB_DIR)/*.o
	rm -rf $(OBJ_DIR)

.PHONY: all d64 run run-console clean
