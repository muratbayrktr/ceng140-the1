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

void copy_area(int image[MAXHEIGHT][MAXWIDTH], int copied_area[MAXHEIGHT*MAXWIDTH], int copy_top_left_x, 
                        int copy_top_left_y, int copy_bottom_right_x, int copy_bottom_right_y)
{
    int i, j, k;
    k = 0;
    for (i = copy_top_left_y; i <= copy_bottom_right_y; i++) {
        for (j = copy_top_left_x; j <= copy_bottom_right_x; j++){
            copied_area[k] = image[i][j];
            k++;
        }
    }
    return ;
}

void paste_area(int image[MAXHEIGHT][MAXWIDTH], int copied_area[MAXHEIGHT*MAXWIDTH], int paste_top_left_x, 
                        int paste_top_left_y, int paste_bottom_right_x, int paste_bottom_right_y)
{
    int i, j, k;
    k = 0;
    /* no need to check boundaries since when the iteration 
    is exhausted, the iteration wont exceed limits of copied_area */
    for (i = paste_top_left_y; i <= paste_bottom_right_y; i++) {
        for (j = paste_top_left_x; j <=paste_bottom_right_x; j++){
            image[i][j] = copied_area[k];
            k++;
        }
    }
    return ;
}

void rotate_area(int image[MAXHEIGHT][MAXWIDTH],int area_to_be_rotated[MAXHEIGHT][MAXWIDTH],char rotation_direction, int rotation_degree,int copy_top_left_x, 
                        int copy_top_left_y, int copy_bottom_right_x, int copy_bottom_right_y, int paste_top_left_y, int paste_bottom_right_x, int len)
{
    /* just a funny implementation */
    int my_cos(int degree), my_sin(int degree);
    int x, y, k, new_x, new_y;
    int color;
    /* correcting the rotation direction for the rotation matris */
    if (rotation_direction == 'R') rotation_degree = 360 - rotation_degree;
    printf("%d %d\n",paste_top_left_y,paste_bottom_right_x);
    
    k = 0;
    for (y = copy_top_left_y; y <= copy_bottom_right_y; y++) {
        for (x = copy_top_left_x; x <= copy_bottom_right_x; x++){
            
            area_to_be_rotated[y][x] = image[y][x];
            k++;
        }
    }
    k = 0;
    for (y = copy_top_left_y; y <= copy_bottom_right_y; y++) {
        for (x = copy_top_left_x; x <= copy_bottom_right_x; x++){
            
            color = area_to_be_rotated[y][x];
                        /* rotating the point */
            new_x = (x+(len/2))*my_cos(rotation_degree) - (y+(len/2))*my_sin(rotation_degree);
            new_y = (x+(len/2))*my_sin(rotation_degree) + (y+(len/2))*my_cos(rotation_degree);
            printf("old (%d,%d) --> (%d,%d) color: %d << %d\n",y,x,new_y,new_x,color,len);
            image[new_y][new_x] = color;
            k++;
        }
    }

    return ;
}

int normalizer(int len, char direction) {
    return 0;
}


void print_array(int image[MAXHEIGHT][MAXWIDTH])
{
    int i, j;
    for (i = 0; i < MAXHEIGHT; i++) 
    {
        for (j = 0; j < MAXHEIGHT; j++) 
        {
            printf("%d ",image[i][j]);
        }
        printf("\n");
    }
    return ;
}

void read_array(int image[MAXHEIGHT][MAXWIDTH]) 
{
    int i, j;
    for (i = 0; i < MAXHEIGHT; i++) 
    {
        for (j = 0; j < MAXHEIGHT; j++) 
        {
            int read;
            scanf(" %d",&read);
            image[i][j] = read;
        }
    }
    return ;
}

int my_cos(int degree)
{
    switch (degree)
    {
    case 0:
        return 1;
    case 90:
        return 0;
    case 180:
        return -1;
    case 270:
        return 0;
    }
    return 0;
}

int my_sin(int degree)
{
    switch (degree)
    {
    case 0:
        return 0;
    case 90:
        return 1;
    case 180:
        return 0;
    case 270:
        return -1;
    }
    return 0;
}

int main(void) 
{
    /* function declarations */
    int decide_color(int color_select[COORDINATE_DIMENSION], int image[MAXHEIGHT][MAXWIDTH]), my_sin(int degree), my_cos(int degree);
    void fill_image(int image[MAXHEIGHT][MAXWIDTH], int y, int x, int color);
    void print_array(int array[MAXHEIGHT][MAXWIDTH]);
    void read_array(int array[MAXHEIGHT][MAXWIDTH]);
    void copy_area(int image[MAXHEIGHT][MAXWIDTH], int copied_area[], int copy_x1, int copy_y1, int copy_x2, int copy_y2);
    void paste_area(int image[MAXHEIGHT][MAXWIDTH], int copied_area[], int paste_x1, int paste_y1, int paste_x2, int paste_y2);
    void rotate_area(int image[MAXHEIGHT][MAXWIDTH],int area_to_be_rotated[MAXHEIGHT][MAXWIDTH],char rotation_direction, int rotation_degree,int copy_top_left_x, 
                        int copy_top_left_y, int copy_bottom_right_x, int copy_bottom_right_y, int paste_top_left_y, int paste_top_left_x, int len);

    /* variable declarations */
    int image[MAXHEIGHT][MAXWIDTH];
    char opcode;

        /* Taking inputs */

    /* 1. taking values as an input to image array */
    read_array(image);

    /* 2. taking operation code as an input */
    scanf(" %c", &opcode);

    /* 3. taking additional inputs according to the opcode */
    switch (opcode)
    {
        case 'F':
            {
                /* local variable declarations */
                int color;
                int color_select[2], fill_coord[2];

                /* take coordinates as in arrays */
                scanf(" %d %d", &color_select[0], &color_select[1]);
                scanf(" %d %d", &fill_coord[0], &fill_coord[1]);

                /* decide color via given coordinates from the image */
                color = decide_color(color_select, image);

                /* actuate the filling */
                fill_image(image, fill_coord[0], fill_coord[1], color);

                /* print out the array after the process */
                print_array(image);
            
                break;
            }
        case 'P':
            {   /* local variable declarations */
                int copy_x1,copy_y1,copy_x2,copy_y2,
                paste_x1,paste_y1,paste_x2,paste_y2;
                int copy_top_left_x, copy_top_left_y, copy_bottom_right_x, copy_bottom_right_y;
                int paste_top_left_x, paste_top_left_y, paste_bottom_right_x, paste_bottom_right_y;
                /* this array is for containing the area and passing it to the paste function */
                int copied_area[MAXHEIGHT*MAXWIDTH];

                /* take coordinates as in arrays */
                scanf(" %d %d %d %d", &copy_y1,&copy_x1,&copy_y2,&copy_x2);
                scanf(" %d %d %d %d", &paste_y1,&paste_x1,&paste_y2,&paste_x2);
                /* define the top left and bottom rights */
                copy_top_left_x = (copy_x1 < copy_x2) ? copy_x1 : copy_x2;
                copy_bottom_right_x = (copy_x1 < copy_x2) ? copy_x2 : copy_x1;
                copy_top_left_y = (copy_y1 < copy_y2) ? copy_y1 : copy_y2;
                copy_bottom_right_y = (copy_y1 < copy_y2) ? copy_y2 : copy_y1;
                paste_top_left_x = (paste_x1 < paste_x2) ? paste_x1 : paste_x2;
                paste_bottom_right_x = (paste_x1 < paste_x2) ? paste_x2 : paste_x1;
                paste_top_left_y = (paste_y1 < paste_y2) ? paste_y1 : paste_y2;
                paste_bottom_right_y = (paste_y1 < paste_y2) ? paste_y2 : paste_y1;
                {
                    /* copy area from the desired coordinates and pass it to the 1-dim array */
                    copy_area(image, copied_area, copy_top_left_x, copy_top_left_y, copy_bottom_right_x, copy_bottom_right_y);

                    /* use 1-dim array to pass the area to the image from the desired coordinates */
                    paste_area(image, copied_area, paste_top_left_x, paste_top_left_y, paste_bottom_right_x, paste_bottom_right_y);

                    /* print out the array after the process */
                    print_array(image);
                }

                break;
            }
        case 'R':
            {   /* local variable declarations */
                int copy_top_left_x, copy_top_left_y, copy_bottom_right_x, copy_bottom_right_y;
                int paste_top_left_x, paste_top_left_y, paste_bottom_right_x, paste_bottom_right_y;
                int rotation_degree;
                char rotation_direction;
                /* this array is for containing the area and passing it to the rotat and paste functions */
                int area_to_be_rotated[MAXHEIGHT][MAXWIDTH];


                /* take degree, direction and also coordinates as in arrays */
                scanf(" %c %d", &rotation_direction, &rotation_degree);
                scanf(" %d %d %d %d", &copy_top_left_y,&copy_top_left_x,&copy_bottom_right_y,&copy_bottom_right_x);
                scanf(" %d %d %d %d", &paste_top_left_y,&paste_top_left_x,&paste_bottom_right_y,&paste_bottom_right_x);

                
                /* copy area from the desired coordinates and pass it to the 1-dim array */
                rotate_area(image, area_to_be_rotated, rotation_direction, rotation_degree, copy_top_left_x, 
                copy_top_left_y, copy_bottom_right_x, copy_bottom_right_y, paste_top_left_y, paste_bottom_right_x,paste_bottom_right_x-paste_top_left_x);

                /* rotate the area according to the degree and rotation */
                print_array(image);
                break;
            }
        default:
            break;
    }  

    return 0;
}