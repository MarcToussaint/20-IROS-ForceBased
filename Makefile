BASE = rai

DEPEND = Core Algo Geo Kin Gui Optim KOMO

build: $(DEPEND:%=inPath_makeLib/%)

installUbuntuAll: $(DEPEND:%=inPath_installUbuntu/%)

printUbuntuAll: $(DEPEND:%=inPath_printUbuntu/%) printUbuntu

clean: $(DEPEND:%=inPath_clean/%)

include $(BASE)/build/generic.mk

.NOTPARALLEL:
