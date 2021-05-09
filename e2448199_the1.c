#include <stdio.h>
#define MAXWIDTH 25
#define MAXHEIGHT 25
#define COORDINATE_DIMENSION 2


void fill_image(int image[MAXHEIGHT][MAXWIDTH], 
                int y, int x, 
                int color_to_fill,int prev_color, int direction)
{
    /* boundary check */
    if (y >= MAXHEIGHT || x >= MAXWIDTH || y < 0 || x < 0) return ;

    
    /* change the color */
    if (image[y][x] == prev_color && image[y][x] != color_to_fill)
    {
        image[y][x] = color_to_fill;
    }
    else return;
    
    /* check the direction that you come, even if we call these functions
    it won't go forever however it'll invade some space in the call stack. We don't want that. */

    /* left */
    if (direction != 3)
        fill_image(image, y, x-1, color_to_fill, prev_color, 7);

    /* top-left */
    if (direction != 4)
        fill_image(image, y-1, x-1, color_to_fill, prev_color, 0);

    /* top */
    if (direction != 5)    
        fill_image(image, y-1, x, color_to_fill, prev_color, 1);

    /* top-right */
    if (direction != 6)
        fill_image(image, y-1, x+1, color_to_fill, prev_color, 2);

    /* right */
    if (direction != 7)
        fill_image(image, y, x+1, color_to_fill, prev_color, 3);

    /* bottom-right */
    if (direction != 0)
        fill_image(image, y+1, x+1, color_to_fill, prev_color, 4);

    /* bottom */
    if (direction != 1)
        fill_image(image, y+1, x, color_to_fill, prev_color, 5);

    /* bottom-left */
    if (direction != 2)
        fill_image(image, y+1, x-1, color_to_fill, prev_color, 6);

    return ;
}

int decide_color(int color_select[COORDINATE_DIMENSION], int image[MAXHEIGHT][MAXWIDTH])
{
    /* 
    I could have coded it with 8 ifs and 1 else however then it would check 8 different situations
    and if the color is at 8. if then it would take time. 

    When it's done with 12 if's like this, the access is faster.
    There are at most 7 ifs to check to reach the desired region. 
    However mostly it wouldn't take that much.
    
    */
    if (color_select[0] < 0) {
        if (color_select[1] < 0) {
            return 0;
        } else if (color_select[1] >= MAXWIDTH) {
            return 2;
        } else {
            return 1;
        }
    } else if (color_select[1] < 0) {
        if (color_select[0] < 0) {
            return 0;
        } else if (color_select[0] >= MAXHEIGHT) {
            return 6;
        } else {
            return 7;
        }
    } else if (color_select[0] >= MAXHEIGHT) {
        if (color_select[1] < 0) {
            return 6;
        } else if (color_select[1] >= MAXWIDTH) {
            return 4;
        } else {
            return 5;
        }
    } else if (color_select[1] >= MAXWIDTH) {
        if (color_select[0] < 0) {
            return 2;
        } else if (color_select[0] >= MAXHEIGHT) {
            return 4;
        } else {
            return 3;
        }        
    } else {
        return image[color_select[0]][color_select[1]];
    }
}

/* for simple copy paster operation we don't need to create 2-D array, because after all 
it will be stored sequencially in the memory and if we use the same algorithm for copying and 
pasting, it won't make difference. */

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

int paste_area(int image[MAXHEIGHT][MAXWIDTH], int copied_area[MAXHEIGHT*MAXWIDTH], int paste_top_left_x, 
                        int paste_top_left_y, int paste_bottom_right_x, int paste_bottom_right_y)
{
    int i, j, k, affected;
    k = affected = 0;
    
    /* no need to check boundaries since when the iteration 
    is exhausted, the iteration wont exceed limits of copied_area */
    for (i = paste_top_left_y; i <= paste_bottom_right_y; i++) {
        for (j = paste_top_left_x; j <=paste_bottom_right_x; j++){
            if (image[i][j] != copied_area[k]) 
                affected++;
            image[i][j] = copied_area[k];
            k++;
        }
    }
    return affected;
}

void copy_area_for_rotate(int image[MAXHEIGHT][MAXWIDTH], int copied_area[MAXHEIGHT][MAXWIDTH], int copy_top_left_x, 
                        int copy_top_left_y, int copy_bottom_right_x, int copy_bottom_right_y)
{
    int i, j, k, m;
    k = m = 0;
    for (i = copy_top_left_y; i <= copy_bottom_right_y; i++) {
        for (j = copy_top_left_x; j <= copy_bottom_right_x; j++){
            copied_area[k][m] = image[i][j];
            m++;
        }
        m = 0;
        k++;
    }
    return ;
}

int paste_area_for_rotate(int image[MAXHEIGHT][MAXWIDTH], int copied_area[MAXHEIGHT][MAXWIDTH], int paste_top_left_x, 
                        int paste_top_left_y, int paste_bottom_right_x, int paste_bottom_right_y)
{
    int i, j, k, m;
    int affected = 0;
    k = m = 0;
    
    /* no need to check boundaries since when the iteration 
    is exhausted, the iteration wont exceed limits of copied_area */
    for (i = paste_top_left_y; i <= paste_bottom_right_y; i++) {
        for (j = paste_top_left_x; j <=paste_bottom_right_x; j++){
            if (image[i][j] != copied_area[k][m]) 
                affected++;
            image[i][j] = copied_area[k][m];
            m++;
        }
        m=0;

        k++;
    }
    return affected;
}

void rotate_area(int image[MAXHEIGHT][MAXWIDTH],int area_to_be_rotated[MAXHEIGHT][MAXWIDTH], int helper[MAXHEIGHT][MAXWIDTH], 
                        char rotation_direction, int rotation_degree,int len)
{
    /* just a funny implementation */
    int my_cos(int degree), my_sin(int degree);
    void print_array();
    int x, y, new_x, new_y, x_add, y_add;
    int color;

    /* correcting the rotation direction for the rotation matris */
    if (rotation_direction == 'L' && rotation_degree != 0) rotation_degree = 360 - rotation_degree;

    /* normalizing the rotated array in itself */
    switch (rotation_degree)
    {
    case 90:
        {
            x_add = len-1;
            y_add = 0;
            break;
        }
     case 180:
        {
            x_add = len-1;
            y_add = len-1;
            break;
        }       
    case 270:
        {
            x_add = 0;
            y_add = len-1;
            break;
        }        
    default:
            x_add = 0;
            y_add = 0;
        break;
    }

    /* rotating area */
    y = x = 0;
    while (y < len)
    {
        while (x < len)
        {
            color = area_to_be_rotated[y][x];
            new_x = x*my_cos(rotation_degree) - y*my_sin(rotation_degree) + x_add;
            new_y = x*my_sin(rotation_degree) + y*my_cos(rotation_degree) + y_add;
            helper[new_y][new_x] = color;
            x++;
        }
        x = 0;
        y++;
    }

    return ;
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
    void fill_image(int image[MAXHEIGHT][MAXWIDTH], int y, int x, int color, int prev_color,int direction);
    void print_array(int array[MAXHEIGHT][MAXWIDTH]);
    void read_array(int array[MAXHEIGHT][MAXWIDTH]);
    void copy_area(int image[MAXHEIGHT][MAXWIDTH], int copied_area[], int copy_x1, int copy_y1, int copy_x2, int copy_y2);
    int paste_area(int image[MAXHEIGHT][MAXWIDTH], int copied_area[], int paste_x1, int paste_y1, int paste_x2, int paste_y2);
    void copy_area_for_rotate(int image[MAXHEIGHT][MAXWIDTH], int copied_area[MAXHEIGHT][MAXWIDTH], int copy_top_left_x, 
                        int copy_top_left_y, int copy_bottom_right_x, int copy_bottom_right_y);
    int paste_area_for_rotate(int image[MAXHEIGHT][MAXWIDTH], int copied_area[MAXHEIGHT][MAXWIDTH], int paste_top_left_x, 
                        int paste_top_left_y, int paste_bottom_right_x, int paste_bottom_right_y);
    void rotate_area(int image[MAXHEIGHT][MAXWIDTH],int area_to_be_rotated[MAXHEIGHT][MAXWIDTH], int helper[MAXHEIGHT][MAXWIDTH], 
                        char rotation_direction, int rotation_degree,int len);
    
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

                {
                    /* decide color via given coordinates from the image */
                    color = decide_color(color_select, image);

                    /* actuate the filling */
                        /* the number 8 here is just a trivial number, which is not in the interval I=[0,7]. Because we should check
                        every corner on the first filling operation, then we move one direction and then we'll keep track of the 
                        last moved direction */
                    fill_image(image, fill_coord[0], fill_coord[1], color, image[fill_coord[0]][fill_coord[1]],8);

                    /* print out the array after the process */
                    print_array(image);
                }
                break;
            }
        case 'P':
            {   /* local variable declarations */
                int copy_x1,copy_y1,copy_x2,copy_y2,
                paste_x1,paste_y1,paste_x2,paste_y2;
                int copy_top_left_x, copy_top_left_y, copy_bottom_right_x, copy_bottom_right_y;
                int paste_top_left_x, paste_top_left_y, paste_bottom_right_x, paste_bottom_right_y;
                int affected_pixels;
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
                    affected_pixels = paste_area(image, copied_area, paste_top_left_x, paste_top_left_y, paste_bottom_right_x, paste_bottom_right_y);

                    /* print out the array after the process */
                    print_array(image);

                    /* print the affected pixels after the array */
                    printf("%d\n",affected_pixels);
                }

                break;
            }
        case 'R':
            {   /* local variable declarations */
                int copy_top_left_x, copy_top_left_y, copy_bottom_right_x, copy_bottom_right_y;
                int paste_top_left_x, paste_top_left_y, paste_bottom_right_x, paste_bottom_right_y;
                int rotation_degree;
                int affected_pixels;
                char rotation_direction;
                /* this array is for containing the area and passing it to the rotat and paste functions */
                int area_to_be_rotated[MAXHEIGHT][MAXWIDTH] = {0}, helper[MAXHEIGHT][MAXWIDTH] = {0};


                /* take degree, direction and also coordinates as in arrays */
                scanf(" %c %d", &rotation_direction, &rotation_degree);
                scanf(" %d %d %d %d", &copy_top_left_y,&copy_top_left_x,&copy_bottom_right_y,&copy_bottom_right_x);
                scanf(" %d %d %d %d", &paste_top_left_y,&paste_top_left_x,&paste_bottom_right_y,&paste_bottom_right_x);

                
                {
                    /* copy are to the two dimensional array for rotation process */
                    copy_area_for_rotate(image, area_to_be_rotated, copy_top_left_x, copy_top_left_y, copy_bottom_right_x, copy_bottom_right_y);

                    /* copy area from the desired coordinates and pass it to the 1-dim array */
                    rotate_area(image, area_to_be_rotated, helper, rotation_direction, rotation_degree,copy_bottom_right_y-copy_top_left_y+1);
                    
                    /* while pasting the pixels check if they are equal and return the affected pixels */
                    affected_pixels = paste_area_for_rotate(image, helper, paste_top_left_x, paste_top_left_y, paste_bottom_right_x, paste_bottom_right_y);
                    
                    /* rotate the area according to the degree and rotation */
                    print_array(image);

                    /* print the affected pixels */
                    printf("%d\n",affected_pixels);
                }

                break;
            }
        default:
            break;
    }  
    return 0;
}