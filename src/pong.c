#include <stdio.h>

void play_pong(int play);

int main() {
    char key;
    printf("\033[0d\033[2J");
    printf("Welcome to the Pong! One of the first computer games in the world.\n");
    printf("Press any key to start game!\n");
    printf("If you want to quit the game - press q.\n");
    scanf("%c", &key);
    if (key != 'q') {
        play_pong(1);
    } else if (key == 'q') {
        return 0;
    }
    return 0;
}

void play_pong(int play) {
    char key;
    /* счет */
    int first_player_score = 0;
    int second_player_score = 0;
    /* свойства шарика */
    char ball = '@';
    int ball_x = 43;
    int ball_y = 12;
    int ball_x_direction = 1;
    int ball_y_direction = 1;
    /* свойства ракеток */
    char racket = '$';
    int first_racket_upper_coord = 3;
    int first_racket_down_coord = 5;
    int second_racket_upper_coord = 19;
    int second_racket_down_coord = 21;
    int first_racket_x = 2;
    int second_racket_x = 77;
    /* свойства игрового поля */
    int field_max_lenght = 80;
    int field_max_height = 25;
    int field[field_max_height][field_max_lenght];
    char space = ' ';
    char vertical_border = '|';
    char horizontal_border = '=';
    printf("\033[0d\033[2J");

    while (play) {
        printf("\033[0d\033[2J");
        /* подсчет голов и конец игры */
        if (ball_x == (field_max_lenght - 1) && first_player_score == 20) {
            first_player_score++;
            printf("Congratulations First Player Win!\n");
            play = 0;
            break;
        }
        if (ball_x == (field_max_lenght - 1)) {
            first_player_score++;
            ball_x = 37;
            ball_y = 12;
            ball_x_direction *= -1;
        }
        if (ball_x == 0 && second_player_score == 20) {
            second_player_score++;
            printf("Congratulations Second Player Win!\n");
            play = 0;
            break;
        }
        if (ball_x == 0) {
            second_player_score++;
            ball_x = 43;
            ball_y = 12;
            ball_x_direction *= -1;
        }

        /* заполнение значениями поля */
        for (int i = 0; i < field_max_height; i++) {
            for (int j = 0; j < field_max_lenght; j++) {
                if (i == 0 || i == (field_max_height - 1)) {
                    field[i][j] = horizontal_border;
                } else if ((j == 40 || j == 39)) {
                    if (ball_x != j) {
                        field[i][j] = vertical_border;
                    }
                    if (i == ball_y && j == ball_x){
                        field[i][j] = ball;
                    }
                } else if (i == ball_y && j == ball_x) {
                    field[i][j] = ball;
                } else if (i >= first_racket_upper_coord && i <= first_racket_down_coord &&
                           j == first_racket_x) {
                    field[i][j] = racket;
                } else if (i >= second_racket_upper_coord && i <= second_racket_down_coord &&
                           j == second_racket_x) {
                    field[i][j] = racket;
                } else if ((i != 0 && i != field_max_height) || (j != 0 && j != field_max_lenght)) {
                    field[i][j] = space;
                }
            }
        }

        /* попадания шарика в ракетку и в стенку */
        if ((first_racket_down_coord >= ball_y && ball_y >= first_racket_upper_coord &&
             ball_x == first_racket_x + 1) ||
            (second_racket_down_coord >= ball_y && ball_y >= second_racket_upper_coord &&
             ball_x == second_racket_x - 1)) {
            if (ball_x == second_racket_x - 1) {
                ball_x_direction = -1;
            } else if (ball_x == first_racket_x + 1) {
                ball_x_direction = 1;
            }
        }

        if (ball_y == 1) {
            ball_y_direction = 1;
        }

        if (ball_y == 23) {
            ball_y_direction = -1;
        }

        /* прорисовка поля */
        for (int i = 0; i < field_max_height; i++) {
            for (int j = 0; j < field_max_lenght; j++) {
                printf("%c", field[i][j]);
            }
            printf("%c", '\n');
        }

        /* счет в игре, приветствие и инструкция */
        printf("\nFirst Player %d : %d Second Player\n\n", first_player_score, second_player_score);
        printf("================================================================================\n\n");
        printf("Use a/z & k/m keys for change rackets positions and Space Bar for skip the turn.\n");
        printf("The game will be over when one of the players scores 21 points. Enjoy!\n");
        printf("If you want to stop the game - press q.\n\n");
        printf("================================================================================\n\n");

        key = getchar();

        /* движения ракетки */
        if ((key == 'z' || key == 'Z')) {
            if (first_racket_down_coord <= (field_max_height - 3)) {
                first_racket_upper_coord++;
                first_racket_down_coord++;
            }
            ball_x += ball_x_direction;
            ball_y += ball_y_direction;
        }

        if ((key == 'a' || key == 'A')) {
            if (first_racket_upper_coord > 1) {
                first_racket_upper_coord--;
                first_racket_down_coord--;
            }

            ball_x += ball_x_direction;
            ball_y += ball_y_direction;
        }

        if ((key == 'k' || key == 'K')) {
            if (second_racket_upper_coord > 1) {
                second_racket_upper_coord--;
                second_racket_down_coord--;
            }
            ball_x += ball_x_direction;
            ball_y += ball_y_direction;
        }

        if ((key == 'm' || key == 'M')) {
            if (second_racket_down_coord <= (field_max_height - 3)) {
                second_racket_upper_coord++;
                second_racket_down_coord++;
            }

            ball_x += ball_x_direction;
            ball_y += ball_y_direction;
        }

        /* движение шарика */
        if (key == ' ') {
            ball_x += ball_x_direction;
            ball_y += ball_y_direction;
        }

        if (key == 'q' || key == 'Q') {
            printf("\033[0d\033[2J");
            printf("Вы вышли из игры.\n");
            break;
        }
    }
}
