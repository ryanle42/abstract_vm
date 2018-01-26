NAME = avm

OBJS = $(addprefix ./srcs/, \
					$(addsuffix .o, \
							OperandFactory \
							VirtualMachine \
							main \
						) \
				)

CXFLAGS = -Wall -Werror -Wextra --std=c++0x

INCLUDES = -I includes

CX = @g++

all: $(NAME)

$(NAME): $(OBJS)
	$(CX) $(CXFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "avm made"

%.o: %.cpp
	$(CX) $(CXFLAGS) $(INCLUDES) -c -o $@ $<

force: 
	@true

clean:
	@rm -f $(OBJS)
	@echo "~~~clean~~~"

fclean: clean
	@rm -f $(NAME)

re: fclean all