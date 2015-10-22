CC = gcc
GEOMDIR = geom
GEOMOBJ = color.o intersect.o material.o point.o ray.o sphere.o triangle.o vec.o
OBJ = raytracer.o $(addprefix $(GEOMDIR)/,$(GEOMOBJ))
EXEC = ray

$(GEOMDIR)/%.o: %.c
	$(CC) -c -o $@ $<

%.o: %.c
	$(CC) -c -o $@ $<

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -f $(EXEC) $(GEOMDIR)/*.o *.o
