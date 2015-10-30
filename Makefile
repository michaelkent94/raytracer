CC = gcc
GEOMDIR = geom
GEOMOBJ = color intersect material point ray sphere triangle vec
OBJ = $(addsuffix .o, raytracer $(addprefix $(GEOMDIR)/,$(GEOMOBJ)))
OBJDIR = obj
EXEC = ray
CFLAGS = -std=gnu99 -Wall -Wextra

%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(notdir $@) $<

$(EXEC): $(OBJ)
	$(CC) -o $@ $(addprefix $(OBJDIR)/,$(notdir $^))

clean:
	rm -rf $(EXEC) $(OBJDIR) reference.png custom.png
