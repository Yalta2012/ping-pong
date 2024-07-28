#include <stdio.h>

#define FIELD_X_SIZE 80
#define FIELD_Y_SIZE 25
#define SPEED 1 // cells per turn
void game();

int change_direction(int ball_x_pos, int ball_y_pos, int rocket_a_pos, int rocket_b_pos, int direction);
void render_field(int ball_x_pos, int ball_y_pos, int rocket_a_pos, int rocket_b_pos, int score_a, int score_b);
int change_pos(int ball_x_pos, int ball_y_pos, int direction);

int main()
{
    game();
    return 0;
}

void game()
{
    int ball_x_pos = 1,
        ball_y_pos = FIELD_Y_SIZE / 2 + 1,
        rocket_a_pos = FIELD_Y_SIZE / 2 + 1,
        rocket_b_pos = FIELD_Y_SIZE / 2 + 1,
        score_a = 0,
        score_b = 0,
        direction = 3;
    char input;
    int move_flag = 0;
    int i;
    int ball_coords;
    printf("%d %d direction: %d\n", ball_x_pos, ball_y_pos, direction);
    render_field(ball_x_pos, ball_y_pos, rocket_a_pos, rocket_b_pos, score_a, score_b);

    while (score_a < 21 && score_b < 21)
    {
        scanf("%c", &input);
        if (input == '\n')
        {
            continue;
        }
        if ((input == 'a' || input == 'A') && rocket_a_pos > 1)
        {
            rocket_a_pos--;
            move_flag = 1;
        }
        else if ((input == 'z' || input == 'Z') && rocket_a_pos < FIELD_Y_SIZE - 1)
        {
            rocket_a_pos++;
            move_flag = 1;
        }
        else if ((input == 'k' || input == 'K') && rocket_b_pos > 1)
        {
            rocket_b_pos--;
            move_flag = 1;
        }
        else if ((input == 'm' || input == 'M') && rocket_b_pos < FIELD_Y_SIZE - 1)
        {
            rocket_b_pos++;
            move_flag = 1;
        }
        else if (input == ' ')
        {
            move_flag = 1;
        }

        if (move_flag)
        {
            printf("%d %d direction: %d\n", ball_x_pos, ball_y_pos, direction);

            for (i = 0; i < SPEED; i++)
            {
                direction = change_direction(ball_x_pos, ball_y_pos, rocket_a_pos, rocket_b_pos, direction);
                ball_coords = change_pos(ball_x_pos, ball_y_pos, direction);
                ball_x_pos = ball_coords / 100;
                ball_y_pos = ball_coords % 100;
            }
        }
        printf("%d %d direction: %d\n", ball_x_pos, ball_y_pos, direction);
        render_field(ball_x_pos, ball_y_pos, rocket_a_pos, rocket_b_pos, score_a, score_b);
        move_flag = 0;
    }
};
int change_direction(int ball_x_pos, int ball_y_pos, int rocket_a_pos, int rocket_b_pos, int direction)
{
    if (ball_x_pos == 1 && ball_y_pos==0 && ball_y_pos <= rocket_a_pos + 1 && ball_y_pos >= rocket_a_pos - 1)
    {
        return (direction + 2) % 4;
    }
    else if (ball_y_pos <= rocket_a_pos + 1 && ball_y_pos >= rocket_a_pos - 1)
    {
        return (direction - 1) / 2 + 2;
    }
    if (ball_x_pos == FIELD_X_SIZE - 1 && ball_y_pos <= rocket_b_pos + 1 && ball_y_pos >= rocket_b_pos - 1)
    {
        return (direction + 2) % 4;
    }
    else if (ball_y_pos <= rocket_b_pos + 1 && ball_y_pos >= rocket_b_pos - 1)
    {
        return direction + 1;
    }
    if (ball_y_pos == 0 || ball_y_pos == FIELD_Y_SIZE - 1)
    {
        return (4 * direction) % 5;
    }

    return direction;
}

int change_pos(int ball_x_pos, int ball_y_pos, int direction)
{
    int new_x = ball_x_pos, new_y = ball_y_pos;
    if (direction <= 2)
        new_y--;
    else
        new_y++;
    if ((3 * direction + 1) % 5 >= 3)
        new_x--;
    else
        new_x++;
    return new_x * 100 + new_y;
}
void render_field(int ball_x_pos, int ball_y_pos, int rocket_a_pos, int rocket_b_pos, int score_a, int score_b)
{
    int y, x;
    for (x = 0; x < FIELD_X_SIZE + 4; x++)
    {
        printf("-");
    }
    printf("\n");
    for (y = 0; y < FIELD_Y_SIZE; y++)
    {

        printf("| ");
        for (x = 0; x < FIELD_X_SIZE; x++)
        {
            if (x == ball_x_pos && y == ball_y_pos)
            {
                printf("O");
                continue;
            }
            if ((x == 0 && y <= rocket_a_pos + 1 && y >= rocket_a_pos - 1) || (x == FIELD_X_SIZE - 1 && y <= rocket_b_pos + 1 && y >= rocket_b_pos - 1))
            {
                printf("|");
                continue;
            }
            printf(" ");
        }
        printf(" |\n");
    }
    for (x = 0; x < FIELD_X_SIZE + 4; x++)
    {
        printf("-");
    }
    printf("\n");
    for (x = 0; x < FIELD_X_SIZE + 4; x++)
    {
        if (x == FIELD_X_SIZE / 2 - 4)
            printf("%2d", score_a);
        else if (x == FIELD_X_SIZE / 2)
            printf("%2d", score_b);
        else
            printf(" ");
    }
    printf("\n");
}
