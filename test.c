#include <stdio.h>

#define FIELD_X_SIZE 80
#define FIELD_Y_SIZE 25
#define SPEED 1  // cells per turn

int game();
int change_direction(int ball_x_pos, int ball_y_pos, int direction, int rocket_a_pos, int rocket_b_pos);
void render_field(int ball_x_pos, int ball_y_pos, int rocket_a_pos, int rocket_b_pos, int score_a,
                  int score_b);
int change_pos(int ball_x_pos, int ball_y_pos, int direction);

int main() {
    int score_a = 0;
    int score_b = 0;

    while (score_a < 21 && score_b < 21) {
        if (game(score_a, score_b) == 1) {
            score_a++;
        } else
            score_b++;
    }
    printf("\nPLAYER %d WIN!!!\n", score_a > score_b ? 1 : 2);
    // printf("%d",change_direction(78,0,2,0,1));
    return 0;
}

int game(int score_a, int score_b) {
    int ball_x_pos = 1, ball_y_pos = FIELD_Y_SIZE / 2 + 1, rocket_a_pos = FIELD_Y_SIZE / 2 + 1,
        rocket_b_pos = FIELD_Y_SIZE / 2 + 1, direction = 3;
    char input;
    int move_flag = 0;
    int i;
    int ball_coords;
    int turn = (score_a + score_b) / 2 % 2;
    if (turn) {
        ball_x_pos = FIELD_X_SIZE - 2;
        direction = 4;
    }
    render_field(ball_x_pos, ball_y_pos, rocket_a_pos, rocket_b_pos, score_a, score_b);

    while (1) {
        scanf("%c", &input);

        if (input == '\n') {
            continue;
        }
        if (input == ' ') {
            printf("%d %d direction: %d\n", ball_x_pos, ball_y_pos, direction);

            ball_coords = change_pos(ball_x_pos, ball_y_pos, direction);
            ball_x_pos = ball_coords / 100;
            ball_y_pos = ball_coords % 100;
            printf("%d %d direction: %d\n", ball_x_pos, ball_y_pos, direction);

            render_field(ball_x_pos, ball_y_pos, rocket_a_pos, rocket_b_pos, score_a, score_b);

            break;
        }
        if ((input == 'a' || input == 'A') && rocket_a_pos > 1) {
            rocket_a_pos--;

            !turn ? ball_y_pos-- : 0;
        } else if ((input == 'z' || input == 'Z') && rocket_a_pos < FIELD_Y_SIZE - 2) {
            rocket_a_pos++;
            !turn ? ball_y_pos++ : 0;
        } else if ((input == 'k' || input == 'K') && rocket_b_pos > 1) {
            rocket_b_pos--;
            turn ? ball_y_pos-- : 0;
        } else if ((input == 'm' || input == 'M') && rocket_b_pos < FIELD_Y_SIZE - 2) {
            rocket_b_pos++;
            turn ? ball_y_pos++ : 0;
        }
        render_field(ball_x_pos, ball_y_pos, rocket_a_pos, rocket_b_pos, score_a, score_b);
    }
    while (1) {
        scanf("%c", &input);
        if (input == '\n') {
            continue;
        }
        if ((input == 'a' || input == 'A') && rocket_a_pos > 1) {
            rocket_a_pos--;
            move_flag = 1;
        } else if ((input == 'z' || input == 'Z') && rocket_a_pos < FIELD_Y_SIZE - 2) {
            rocket_a_pos++;
            move_flag = 1;
        } else if ((input == 'k' || input == 'K') && rocket_b_pos > 1) {
            rocket_b_pos--;
            move_flag = 1;
        } else if ((input == 'm' || input == 'M') && rocket_b_pos < FIELD_Y_SIZE - 2) {
            rocket_b_pos++;
            move_flag = 1;
        } else if (input == ' ') {
            move_flag = 1;
        }
        // printf("x:%d y:%d dir:%d\n", ball_x_pos, ball_y_pos, direction);
        if (move_flag) {
            for (i = 0; i < SPEED; i++) {
                direction = change_direction(ball_x_pos, ball_y_pos, direction, rocket_a_pos, rocket_b_pos);
                ball_coords = change_pos(ball_x_pos, ball_y_pos, direction);
                ball_x_pos = ball_coords / 100;
                ball_y_pos = ball_coords % 100;
            }
        }
        // printf("x:%d y:%d dir:%d\n", ball_x_pos, ball_y_pos, direction);

        render_field(ball_x_pos, ball_y_pos, rocket_a_pos, rocket_b_pos, score_a, score_b);
        move_flag = 0;
        if (ball_x_pos == 0) return 2;
        if (ball_x_pos == FIELD_X_SIZE - 1) return 1;
    }
};

int change_direction(int ball_x_pos, int ball_y_pos, int direction, int rocket_a_pos, int rocket_b_pos) {
    if (ball_x_pos == 1 && ball_y_pos <= rocket_a_pos + 1 && ball_y_pos >= rocket_a_pos - 1) {
        if (ball_y_pos <= 1 || ball_y_pos >= FIELD_Y_SIZE - 1) {
            return (direction + 2) % 4;
        }
        return (direction - 1) / 2 + 2;
    }

    if (ball_x_pos == FIELD_X_SIZE - 2 && ball_y_pos <= rocket_b_pos + 1 && ball_y_pos >= rocket_b_pos - 1) {
        if (ball_y_pos <= 1 || ball_y_pos >= FIELD_Y_SIZE - 1) {
            return (direction * 2) % 5;
        }
        return (3 * direction % 5);
    }

    if (ball_y_pos == 0 || ball_y_pos == FIELD_Y_SIZE - 1) {
        return (4 * direction) % 5;
    }

    return direction;
}

int change_pos(int ball_x_pos, int ball_y_pos, int direction) {
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
void render_field(int ball_x_pos, int ball_y_pos, int rocket_a_pos, int rocket_b_pos, int score_a,
                  int score_b) {
    int y, x;
    for (x = 0; x < FIELD_X_SIZE + 4; x++) {
        printf("-");
    }
    printf("\n");
    for (y = 0; y < FIELD_Y_SIZE; y++) {
        printf("| ");
        for (x = 0; x < FIELD_X_SIZE; x++) {
            if (x == ball_x_pos && y == ball_y_pos) {
                printf("O");
                continue;
            }
            if ((x == 0 && y <= rocket_a_pos + 1 && y >= rocket_a_pos - 1) ||
                (x == FIELD_X_SIZE - 1 && y <= rocket_b_pos + 1 && y >= rocket_b_pos - 1)) {
                printf("|");
                continue;
            }
            printf(" ");
        }
        printf(" |\n");
    }
    for (x = 0; x < FIELD_X_SIZE + 4; x++) {
        printf("-");
    }
    printf("\n");
    for (x = 0; x < FIELD_X_SIZE + 4; x++) {
        if (x == FIELD_X_SIZE / 2 - 4)
            printf("%2d", score_a);
        else if (x == FIELD_X_SIZE / 2)
            printf("%2d", score_b);
        else
            printf(" ");
    }
    printf("\n");
}
