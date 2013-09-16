#WIRESHARK_SRC=/usr/local/src/wireshark-1.6.8
#WIRESHARK_PLUGINS=/usr/local/lib/wireshark/plugins/1.6.8/
WIRESHARK_SRC=/usr/include/wireshark
WIRESHARK_PLUGINS=/usr/lib/wireshark/plugins/1.8.5/

PLUGIN_NAME = packet-gg
PLUGIN      = $(PLUGIN_NAME).so

INCS = -I$(WIRESHARK_SRC) -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include

SRCS = \
	packet-gg.c \
	gg-tvb.c \
	gg-bitfield.c \
	gg-packet-type.c \
	gg-dissect-login.c \
	gg-dissect-notify.c \
	gg-dissect-userlist.c \
	gg-dissect-new.c \
	gg-dissect-chat.c

CC = gcc

OBJS = $(foreach src, $(SRCS), $(src:.c=.o))

CFLAGS = -DHAVE_CONFIG_H $(INCS) -DINET6 -D_U_=__attribute__\(\(unused\)\) \
	-Wall -Wextra -Wpointer-arith \
	-g -DXTHREADS -D_REENTRANT -DXUSE_MTSAFE_API -fPIC -DPIC

$(PLUGIN) : $(OBJS)
	$(CC) -shared $(OBJS) -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(PLUGIN) $(OBJS)

install: $(PLUGIN)
	mkdir -p $(WIRESHARK_PLUGINS)
	cp $< $(WIRESHARK_PLUGINS)

uninstall:
	rm $(WIRESHARK_PLUGINS)/$(PLUGIN)
