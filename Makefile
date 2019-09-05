CROSS_PREFIX :=
PP=$(CROSS_PREFIX)cpp
CC=$(CROSS_PREFIX)gcc
LD=$(CROSS_PREFIX)ld
AR=$(CROSS_PREFIX)ar
CCFLAGS=-O3 -pipe -Werror -Wall $(CFLAGS)
LDFLAGS=-pthread

SRCDIR=src
BINDIR=bin
BUILDDIR=build

-include build.mk
CCFLAGS+=-I$(SRCDIR) $(CONFIG_CFLAGS)

CCSRCS=$(filter %.c,$(SRCFILES))
LDOBJS=$(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(CCSRCS))
DEPEND=$(LDOBJS:.o=.dep)

BUILDMSG="\e[1;31mBUILD\e[0m %s\n"
LINKMSG="\e[1;34mLINK\e[0m  \e[1;32m%s\e[0m\n"
CLEANMSG="\e[1;34mCLEAN\e[0m %s\n"
PASSMSG="\e[1;34mTEST\e[0m  \e[1;32m%s\e[0m\t\e[1;32mPASS\e[0m\n"
FAILMSG="\e[1;34mTEST\e[0m  \e[1;32m%s\e[0m\t\e[1;31mFAIL\e[0m\n"

V:=
ECHO_PREFIX:=@
ifeq ($(V),1)
    undefine ECHO_PREFIX
endif

.PHONY: clean tests

tests : $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%,$(wildcard $(SRCDIR)/*.c))
	$(ECHO_PREFIX) for test in $^; do \
		$$test && printf $(PASSMSG) $$test || printf $(FAILMSG) $$test ; \
	done

clean :
	$(ECHO_PREFIX) $(RM) -rf $(BINDIR) $(BUILDDIR)
	@printf $(CLEANMSG)

$(BUILDDIR)/%.dep : $(SRCDIR)/%.c
	$(ECHO_PREFIX) mkdir -p $(dir $@)
	$(ECHO_PREFIX) $(PP) $(CCFLAGS) -MM -MT$(@:.dep=.o) -MF$@ $< 2>/dev/null

$(BUILDDIR)/%.o : $(SRCDIR)/%.c
	$(ECHO_PREFIX) mkdir -p $(dir $@)
	$(ECHO_PREFIX) $(CC) $(CCFLAGS) -c -o $@ $<
	@printf $(BUILDMSG) $<

$(BINDIR)/% : $(BUILDDIR)/%.o
	$(ECHO_PREFIX) mkdir -p $(dir $@)
	$(ECHO_PREFIX) $(CC) -o $@ $^ $(CCFLAGS) $(LDFLAGS)
	@printf $(LINKMSG) $@

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPEND)
endif
