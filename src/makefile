OLD  := MMult0
NEW  := MMult1
#
# sample makefile
#

CC         := g++
LINKER     := $(CC)
CFLAGS     := -O2 -Wall -msse3
LDFLAGS    := -lm

TEST_OBJS  := main.o $(NEW).o 

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	

run:
	make test_MMult.x
	export OMP_NUM_THREADS=1
	export GOTO_NUM_THREADS=1
	echo "version = '$(NEW)';" > output_$(NEW).m
	./test_MMult.x >> output_$(NEW).m
	cp output_$(OLD).m output_old.m
	cp output_$(NEW).m output_new.m
	python PlotAll.py

test_MMult.x: $(TEST_OBJS) parameters.hpp
	$(LINKER) $(TEST_OBJS) $(LDFLAGS) \
        $(BLAS_LIB) -o $(TEST_BIN) $@ 

clean:
	rm -f *.o *~ core *.x output*.m 

cleanall:
	rm -f *.o *~ core *.x output*.m *.eps *.png
