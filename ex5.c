#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ZERO 0

typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
} Song;

typedef struct Playlist {
    char* name;
    Song** songs;
    int songsNum;
} Playlist;
// All the Functions used in the code.
void mainMinu();
void watchPlayslists();
void removePlaylist();
void showPlaylists();
Song* createSong();
void addSong();
void deleteSong();
void sortSongs();
void playSongs();
Playlist *addPlayLists(int* counter);
char* getName();
void clearBuffer();

//some recommendations for functions, you may implement however you want

void deleteSong() {

    printf("Song deleted successfully.\n");
}



void playSong() {
    
}



void freeSong() {

}

void freePlaylist() {
    
}

void printPlaylistsMenu() {
    printf("Please Choose:\n"); 
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");   
}



void sortPlaylist() {
    
    printf("sorted\n");
}



int main() {
    mainMinu();
    return 0;

}
void mainMinu() {
    int numPlaylists;
    int capacity;
    Playlist** playlists = NULL;

    int task ;
    while(1){
        printf("Please Choose:\n"
            "1. Watch playlists\n"
            "2. Add playlist\n"
            "3. Remove playlist\n"
            "4. exit\n");
        scanf("%d", &task);
        clearBuffer();
            switch (task)
            {
                //Show all the playlists
                case 1: {
                    watchPlayslists(&playlists,numPlaylists);
                    break;
                }//Add Playlist
                case 2: {
                    if(numPlaylists  == capacity) {
                        capacity++;
                        playlists = (Playlist**)realloc(playlists,capacity * sizeof(Playlist*));
                        if(!playlists)
                            exit(1);
                    }
                    playlists[numPlaylists]=addPlayLists(&numPlaylists);

                    break;
                }//Remove Playlist
                case 3: {

                }
                case 4: {
                    printf("Goodbye!\n");
                    return;
                }
                default:
                    printf("Invalid option\n");;
            }
        }
    }

void watchPlayslists(Playlist *header,int numPlaylists) {
    printf("Choose a playlist:\n");
    for(int i = 0; i < numPlaylists; i++) {
        printf("%d. %s\n",i+1,header[i].name);
    }
    printf("%d Back to main menu",numPlaylists+1);
    int playlistIndex;
    scanf("%d", &playlistIndex);
    clearBuffer();
    int task;
    while(1) {
        printf("playlist %s\n"
            "1. Show Playlist\n"
            "2. Add Song\n"
            "3. Delete Song\n"
            "4. Sort\n"
            "5. Play\n"
            "6. Back\n",header[playlistIndex-1].name);
        scanf("%d",&task);
        clearBuffer();
        switch(task) {
            //Show the Playlist.
            case 1: {
                printf("choose a song to play, of 0 to quit:\n");

            }//Add Song to the Playlist.
            case 2: {
                addSong(&header);
            }//Delete a Song from the Playlist.
            case 3: {

            }//Sort the Playlist.
            case 4: {

            }//Play all the Songs in the Playlist.
            case 5: {

            }
            case 6:
                return;
        }

    }

}
void addSong(Playlist *playlist) {
    Song* newSong = createSong(playlist->songsNum);
    playlist->songsNum++;
    playlist->songs = (Song**)realloc(playlist->songs,playlist->songsNum*sizeof(Song*));
    if(!*playlist->songs) {
        free(newSong);
        exit(1);
    }
    playlist->songs[playlist->songsNum-1] = newSong;
}
Song* createSong(int *numSongs) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    if(!newSong)
        exit(1);
    (*numSongs)++;
    // Collect song details
    printf("Enter song's details:\n");

    printf("Title: ");
    newSong->title = getName();

    printf("Artist: ");
    newSong->artist = getName();

    printf("Year of release: ");
    scanf("%d", &newSong->year);
    clearBuffer(); // To consume the newline character

    printf("Lyrics: ");
    newSong->lyrics = getName();

    // Set initial streams count
    newSong->streams = 0;
    return newSong;
}

Playlist *addPlayLists( int* counter) {
    Playlist *newplaylist = (Playlist*)malloc(sizeof(Playlist));
    if(newplaylist == NULL) {
        exit(1);
    }
    (*counter)++;
    printf("Enter playlist's name:\n");
    newplaylist->name =getName();
    newplaylist->songs = NULL;
    newplaylist->songsNum = ZERO;
    return newplaylist;
}
void clearBuffer() {
    // Consume any characters remaining in the input buffer until a newline
    scanf("%*[^ \n]"); // This consumes all characters except '\n'
    scanf("%*c");      // This consumes the newline itself
}
// function to allocate unlimited string and return a pointer to it.
char *getName() {
    int len =0;
    char c;
    char *str = (char*)malloc(sizeof(char));
    if (str==NULL)
        exit(1);
    // clearBuffer();
    while ( 1) {
        if(scanf("%c", &c)!=1)
            exit(1);
        if ( c == '\n') {
            break;
        }
        str[len] = c;
        len++;
        str = realloc(str, (len + 1) * sizeof(char));
        if (str == NULL) exit(1);// Increment len separately
        // clearBuffer();
    }
    str[len] = '\0'; // Add null terminator
    return str;
}
