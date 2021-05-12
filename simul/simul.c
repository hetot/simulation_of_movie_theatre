#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

struct Hall {
    bool is_playing;
    int capacity[11][5];
    int id;
    int available_places;
};

struct Ticket {
    int request_timestamp;
    int request_id;
    int num_of_people;
    int movie_id;
    bool is_placed;
};

struct Simulation_engine {
    int total_duration;
    int current_timestamp;
    
};

struct Movies {
    int id;
    int start_time;
    int duration;
    int end_time;
    int hall_id;
    bool is_active;
};

int main(){

    FILE * movie_f;

    movie_f = fopen("Movie.txt", "r");
    
    if(movie_f == NULL){
        printf("Error occured while reading Movie.txt");
        return -1;
    }
    
    struct Movies movie[10];
    int movie_counter = 0;
    
    while (fscanf(movie_f, "%d,%d,%d,%d", &movie[movie_counter].id, &movie[movie_counter].start_time, &movie[movie_counter].duration, &movie[movie_counter].hall_id) != EOF)
    {  
      printf ("%d %d %d %d \n", movie[movie_counter].id, movie[movie_counter].start_time, movie[movie_counter].duration, movie[movie_counter].hall_id);
      movie[movie_counter].is_active = true;
      movie_counter++;
    }
    
    fclose(movie_f);
    
    struct Hall hall[movie_counter];
    
    for (int k = 0; k < movie_counter; k++){
        
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 5; j++){
                if (j == 4){
                    hall[k].capacity[i][j] = -1;
                } else {
                    hall[k].capacity[i][j] = 0;
                }
            }
        }
        for(int i = 6; i < 11; i++){
            for(int j = 0; j < 5; j++){
                hall[k].capacity[i][j] = 0;
            }
        }
        hall[k].id = movie[k].hall_id;
        hall[k].available_places = 49;
    }
    
    struct Simulation_engine engine;
    
    engine.total_duration = movie[movie_counter - 1].start_time + movie[movie_counter - 1].duration;
    engine.current_timestamp = 0;
    
    struct Ticket ticket[100];
    int ticket_counter = 0;
    
    FILE * ticket_f;

    ticket_f = fopen("Ticket.txt", "r");
    
    if(ticket_f == NULL){
        printf("Error occured while reading Ticket.txt");
        return -1;
    }
    
    while (fscanf(ticket_f, "%d,%d,%d,%d", &ticket[ticket_counter].request_timestamp, &ticket[ticket_counter].request_id, &ticket[ticket_counter].num_of_people, &ticket[ticket_counter].movie_id) != EOF)
    {  
      printf ("%d %d %d %d \n", ticket[ticket_counter].request_timestamp, ticket[ticket_counter].request_id, ticket[ticket_counter].num_of_people, ticket[ticket_counter].movie_id);
      ticket[ticket_counter].is_placed = false;
      ticket_counter++;
    }
    
    fclose(ticket_f);
    
    int customers_lost = 0;
    
    for (engine.current_timestamp; engine.current_timestamp < engine.total_duration + 1; engine.current_timestamp++){
        usleep(200);
        printf("timestamp:%d\n", engine.current_timestamp);
        
        for (int i = 0; i < ticket_counter; i++){
            if (ticket[i].request_timestamp == engine.current_timestamp) {
                for (int j = 0; j < movie_counter; j++){
                    if (ticket[i].movie_id == movie[j].id){
                        if (movie[j].is_active == true) {
                            if (hall[j].available_places >= ticket[i].num_of_people){
                                ticket[i].is_placed = true;
                                for(int l = 0; l < 6; l++){
                                    if (ticket[i].num_of_people == 0){
                                        break;
                                    }
                                    for(int m = 0; m < 5; m++){
                                        if (ticket[i].num_of_people == 0){
                                            break;
                                        }
                                        if (hall[j].capacity[l][m] == 0){
                                            hall[j].capacity[l][m] = 1;
                                            hall[j].available_places--;
                                            ticket[i].num_of_people--;
                                        }
                                    }
                                }
                                for(int l = 6; l < 11; l++){
                                    if (ticket[i].num_of_people == 0){
                                        break;
                                    }
                                    for(int m = 0; m < 5; m++){
                                        if (ticket[i].num_of_people == 0){
                                            break;
                                        }
                                        if (hall[j].capacity[l][m] == 0){
                                            hall[j].capacity[l][m] = 1;
                                            hall[j].available_places--;
                                            ticket[i].num_of_people--;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        printf("\n\nCurrent status of movies and halls:\n");
        
        for (int i = 0; i < movie_counter; i++){
            if (engine.current_timestamp == movie[i].start_time){
            	printf("Movie with id:%d is started at hall with id:%d\n", movie[i].id, movie[i].hall_id);
            	movie[i].is_active = false;
            } else if (engine.current_timestamp > movie[i].start_time && engine.current_timestamp < movie[i].start_time + movie[i].duration){
                printf("Movie with id:%d is playing at hall with id:%d\n", movie[i].id, movie[i].hall_id);
            } else if (engine.current_timestamp > movie[i].start_time + movie[i].duration){
                printf("Movie with id:%d is finished playing at hall with id:%d\n", movie[i].id, movie[i].hall_id);
            } else if (engine.current_timestamp < movie[i].start_time){
                printf("Current seats status for movie with id:%d (0 for empty, 1 for ordered) \n", movie[i].id);
                
                for(int l = 0; l < 6; l++){
                    for(int m = 0; m < 5; m++){
                        if(hall[i].capacity[l][m] != -1){
                            printf("%d", hall[i].capacity[l][m]);
                        }
                    }
                    printf("\n");
                }
                for(int l = 6; l < 11; l++){
                    for(int m = 0; m < 5; m++){
                        printf("%d", hall[i].capacity[l][m]);
                    }
                    printf("\n");     
                }
            }
        }
        printf("\n\n");
    }
    
    for (int i = 0; i < ticket_counter; i++){
    	if (ticket[i].is_placed == false){
    	    customers_lost += ticket[i].num_of_people;
    	}
    }
    
    printf("Lost cutomers:%d\n", customers_lost);
    
    return 0;
    
    
    
}

