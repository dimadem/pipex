#include "./include/ft_printf.h"

void	ft_case_character(char character)
{
	int				result;
	printf("-------------------------------\n");
	printf("\n-");
	printf("\nft_printf case character\n");
	result = ft_printf(" %c ", character);
	printf("\nlength -> %d\n", result);

	printf("\n-");
	printf("\nprintf case character\n");
	result = printf(" %c ", character);
	printf("\nlength -> %d\n", result); 
}

void	ft_case_string(char *string)
{

	int				result;
	printf("-------------------------------\n");
	printf("\n-");
	printf("\nft_printf case string\n");
	result = ft_printf("%s", string);
	printf("\nlength -> %d\n", result);

	printf("\n-");
	printf("\nprintf case string\n");
	result = printf("%s", string);
	printf("\nlength -> %d\n", result);

	printf("-------------------------------\n");
	printf("\n-");
	printf("\nft_printf case string NULL\n");
	result = ft_printf(" %p NULL ",  NULL);
	printf("\nlength -> %d\n", result);

	printf("\n-");
	printf("\nprintf case string NULL\n");
	result = printf(" %p NULL ", NULL);
	printf("\nlength -> %d\n", result);
}

void	ft_case_pointer(char *pointer)
{
	int				result;
	printf("-------------------------------\n");
	printf("\n-");
	printf("\nft_printf case pointer char\n");
	result = ft_printf("%p", pointer);
	printf("\nlength -> %d\n", result);

	printf("\n-");
	printf("\nprintf case pointer char\n");
	result = printf("%p", pointer);
	printf("\nlength -> %d\n", result);
}

void	ft_case_pointer_int(int *pointer_int)
{
	int				result;

	printf("-------------------------------\n");
	printf("\n-");
	printf("\nft_printf case pointer int\n");
	result = ft_printf("%p", pointer_int);
	printf("\nlength -> %d\n", result);

	printf("\n-");
	printf("\nprintf case pointer int\n");
	result = printf("%p", pointer_int);
	printf("\nlength -> %d\n", result);
}

void	ft_case_decimal(int number)
{
	int				result;
	printf("-------------------------------\n");
	printf("\n-");
	printf("\nft_printf case decimal\n");
	result = ft_printf("%d", number);
	printf("\nlength -> %d\n", result);

	printf("\n-");
	printf("\nprintf case decimal\n");
	result = printf("%d", number);
	printf("\nlength -> %d\n", result);
}

void	ft_case_integer(int number)
{
	int				result;
	printf("-------------------------------\n");
	printf("\n-");
	printf("\nft_printf case integer\n");
	result = ft_printf("%i", number);
	printf("\nlength -> %d\n", result);

	printf("\n-");
	printf("\nprintf case integer\n");
	result = printf("%i", number);
	printf("\nlength -> %d\n", result);
}

void	ft_case_unsigned(unsigned int number)
{
	int				result;
	printf("-------------------------------\n");
	printf("\n-");
	printf("\nft_printf case unsigned\n");
	result = ft_printf("%u", number);
	printf("\nlength -> %d\n", result);

	printf("\n-");
	printf("\nprintf case unsigned\n");
	result = printf("%u", number);
	printf("\nlength -> %d\n", result);
}

void	ft_case_hexadecimal_lowercase(int number)
{
	int				result;
	printf("-------------------------------\n");
	printf("\nft_printf case hexadecimal lowercase\n");
	result = ft_printf("%x", number);
	printf("\nlength -> %d\n", result);

	printf("\n-");
	printf("\nprintf case hexadecimal lowercase\n");
	result = printf("%x", number);
	printf("\nlength -> %d\n", result);
}

void	ft_case_hexadecimal_uppercase(int number)
{
	int				result;
	printf("\n-");
	printf("\nft_printf case hexadecimal uppercase\n");
	result = ft_printf("%X", number);
	printf("\nlength -> %d\n", result);

	printf("\n-");
	printf("\nprintf case hexadecimal uppercase\n");
	result = printf("%X", number);
	printf("\nlength -> %d\n", result);
}

void	ft_case_percent(void)
{
	int				result;
	printf("-------------------------------\n");
	printf("\n-");
	printf("\nft_printf case percent\n");
	result = ft_printf(" %% %% ");
	printf("\nlength -> %d\n", result);

	printf("\n-");
	printf("\nprintf case percent\n");
	result = printf(" %% %% ");
	printf("\nlength -> %d\n", result);
}

void	ft_case_format_all(char *format_all, char *pointer, int *pointer_int, char *string, int number)
{
	int				result;
	printf("-------------------------------\n");
	printf("\n-");
	printf("\nft_printf case all\n");
	result = ft_printf(format_all, pointer, pointer_int, string, number, number, number);
	printf("\nlength -> %d\n", result);

	printf("\n-");
	printf("\nprintf case all\n");
	result = printf(format_all, pointer, pointer_int, string, number, number, number);
	printf("\nlength -> %d\n", result);
}
int main(void)
{
	int				result;
	char			character = 'c';
	char			string[] = "string";
	int				number = -1;
	char			*pointer;
	int				*pointer_int;
	char			format_all[]="\npointer char  -> %p\npointer int   -> %p\nformat string -> %s\nformat digit  -> %d\nformat hexadecimal lowercase -> %x\nformat hexadecimal Uppercase -> %X\ncase   -> %%";

	ft_case_character(character);
    ft_case_string(string);
	ft_case_pointer(pointer);
	ft_case_pointer_int(pointer_int);
	ft_case_decimal(number);
	ft_case_integer(number);
	ft_case_unsigned(number);
	ft_case_hexadecimal_lowercase(number);
	ft_case_hexadecimal_uppercase(number);
	ft_case_percent();
	ft_case_format_all(format_all, pointer, pointer_int, string, number);
}
