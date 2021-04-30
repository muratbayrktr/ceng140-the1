#include <stdio.h>
#define MAXWIDTH 5
#define MAXHEIGHT 5
#define COORDINATE_DIMENSION 2


void fill_image(int image[MAXHEIGHT][MAXWIDTH], 
                int y, int x, 
                int color)
{
    /* store the old color */
    int current_color = image[y][x];
    /* change the color */
    image[y][x] = color;
    /* boundary check */
    if (y+1 > MAXHEIGHT || x+1 > MAXWIDTH || y-1 < 0 || x-1 < 0) return ;
    /* left */
    if (image[y][x-1] == current_color) {
        fill_image(image, y, x-1, color);
    }
    /* top-left */
    if (image[y-1][x-1] == current_color) {
        fill_image(image, y-1, x-1, color);
    }
    /* top */
    if (image[y-1][x] == current_color) {
        fill_image(image, y-1, x, color);
    }
    /* top-right */
    if (image[y-1][x+1] == current_color) {
        fill_image(image, y-1, x+1, color);
    }
    /* right */
    if (image[y][x+1] == current_color) {
        fill_image(image, y, x+1, color);
    }
    /* bottom-right */
    if (image[y+1][x+1] == current_color) {
        fill_image(image, y+1, x+1, color);
    }
    /* bottom */
    if (image[y+1][x] == current_color) {
        fill_image(image, y+1, x, color);
    }
    /* bottom-left */
    if (image[y+1][x-1] == current_color) {
        fill_image(image, y+1, x-1, color);
    }
    return ;
}

int decide_color(int color_select[COORDINATE_DIMENSION], int image[MAXHEIGHT][MAXWIDTH])
{
    /* 
    I could have coded it with 8 if's however then it would check 8 different situations
    and if the color is at 8. if then it would take time. 

    When it's done with 12 if's like this, the access is faster.
    There are at most 7 ifs to check to reach the desired region. 
    However mostly it wouldn't take that much.
    
    */
    if (color_select[0] < 0) {
        if (color_select[1] < 0) {
            return 0;
        } else if (color_select[1] > MAXWIDTH) {
            return 2;
        } else {
            return 1;
        }
    } else if (color_select[1] < 0) {
        if (color_select[0] < 0) {
            return 0;
        } else if (color_select[0] > MAXHEIGHT) {
            return 6;
        } else {
            return 7;
        }
    } else if (color_select[0] > MAXHEIGHT) {
        if (color_select[1] < 0) {
            return 6;
        } else if (color_select[1] > MAXWIDTH) {
            return 4;
        } else {
            return 5;
        }
    } else if (color_select[1] > MAXWIDTH) {
        if (color_select[0] < 0) {
            return 2;
        } else if (color_select[0] > MAXHEIGHT) {
            return 4;
        } else {
            return 3;
        }        
    } else {
        return image[color_select[0]][color_select[1]];
    }
}

int main(void) 
{
    /* function declarations */
    void fill_image(int image[MAXHEIGHT][MAXWIDTH], int y, int x, int color);
    int decide_color(int color_select[COORDINATE_DIMENSION], int image[MAXHEIGHT][MAXWIDTH]);

    /* variable declarations */
    int i,j;
    int image[MAXHEIGHT][MAXWIDTH];
    char opcode;


        /* Taking inputs */

    /* 1. taking values as an input to image array */
    for (i = 0; i < MAXHEIGHT; i++) 
    {
        for (j = 0; j < MAXHEIGHT; j++) 
        {
            int read;
            scanf(" %d",&read);
            image[i][j] = read;
        }
    }

    /* 2. taking operation code as an input */
    scanf(" %c", &opcode);

    /* 3. taking additional inputs according to the opcode */
    switch (opcode)
    {
        case 'F':
            {
                /* take coordinates as in arrays */
                int color;
                int color_select[2], fill_coord[2];
                scanf(" %d %d", &color_select[0], &color_select[1]);
                scanf(" %d %d", &fill_coord[0], &fill_coord[1]);

                /* decide color via given coordinates from the image */
                color = decide_color(color_select, image);

                /* actuate the filling */
                fill_image(image, fill_coord[0], fill_coord[1], color);

                /* print out the array after the process */
                for (i = 0; i < MAXHEIGHT; i++) 
                {
                    for (j = 0; j < MAXHEIGHT; j++) 
                    {
                        printf("%d ",image[i][j]);
                    }
                    printf("\n");
                }
            
                break;
            }
        case 'P':
            {
                /* code here */
                break;
            }
        case 'R':
            {
                /* code here */
                break;
            }
        default:
            break;
    }  

    return 0;
}