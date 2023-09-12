NAME		= PmergeMe
SRCS		= $(wildcard *.cpp)
OBJS		= $(patsubst %.cpp, %.o, $(SRCS))
CXXPP		= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
RM			= rm -f

%.o: %.cpp
	@$(CXXPP) $(CXXFLAGS) -c $< -o $@

all: $(NAME)
	
$(NAME): $(OBJS)
	@$(CXXPP) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created !$(END)"

clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW)Object files deleted !$(END)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)All deleted !$(END)"

re: fclean all

.PHONY: all clean fclean re

#MakefileColors
GREEN = \033[1;32m
YELLOW = \033[1;33m
RED=\033[0;31m
END = \033[0m