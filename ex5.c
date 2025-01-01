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
void freePlaylist(Playlist* playlist);
void freeSong(Song* song);
void removePlaylist();
void showPlaylist();
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
void sortPlaylist() {
    
    printf("sorted\n");
}

int main() {
    mainMinu();
    return 0;

}
void mainMinu() {
    int numPlaylists = 0;
    int capacity = 1;
    Playlist** playlists = (Playlist**)malloc(sizeof(Playlist*));

    int task ;
    while(1){
        printf("Please Choose:\n"
            "1. Watch playlists\n"
            "2. Add playlist\n"
            "3. Remove playlist\n"
            "4. exit\n");
        scanf("%d", &task);
            switch (task)
            {
                //Show all the playlists
                case 1: {
                    watchPlayslists(playlists,numPlaylists);
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
                    removePlaylist(playlists,&numPlaylists);
                    clearBuffer();
                    break;
                }
                case 4: {
                    printf("Goodbye!\n");
                    for (int i = 0; i < numPlaylists; i++) {
                        freePlaylist(playlists[i]);
                    }
                    free(playlists);
                    return;
                }
                default:
                    printf("Invalid option\n");
            }
        }
    }

void watchPlayslists(Playlist **playlist,int numPlaylists) {
    printf("Choose a playlist:\n");
    for(int i = 0; i < numPlaylists; i++) {
        printf("%d. %s\n",i+1,playlist[i]->name);
    }
    printf("%d. Back to main menu",numPlaylists+1);
    int playlistIndex;
    scanf("%d", &playlistIndex);
    int task;
    while(1) {
        printf("playlist %s\n"
            "1. Show Playlist\n"
            "2. Add Song\n"
            "3. Delete Song\n"
            "4. Sort\n"
            "5. Play\n"
            "6. Back\n",playlist[playlistIndex-1]->name);
        scanf("%d",&task);
        switch(task) {
            //Show the Playlist.
            case 1: {
                printf("choose a song to play, of 0 to quit:\n");
                showPlaylist(playlist[playlistIndex-1]->songs);
                break;

            }//Add Song to the Playlist.
            case 2: {
                addSong(playlist[playlistIndex-1]);
                break;
            }//Delete a Song from the Playlist.
            case 3: {
                break;
            }//Sort the Playlist.
            case 4: {
                break;
            }//Play all the Songs in the Playlist.
            case 5: {
                break;
            }
            case 6:
                return;
        }

    }

}
void addSong(Playlist *playlist) {
    Song* newSong = createSong();
    playlist->songsNum++;
    playlist->songs = (Song**)realloc(playlist->songs,playlist->songsNum*sizeof(Song*));
    if(!*playlist->songs) {
        free(newSong);
        return;
    }
    playlist->songs[playlist->songsNum-1] = newSong;
}
Song* createSong(int *numSongs) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    if(!newSong)
        return NULL;
    // Collect song details
    printf("Enter song's details:\n");

    printf("Title:\n ");
    newSong->title = getName();

    printf("Artist:\n ");
    newSong->artist = getName();

    printf("Year of release:\n ");
    scanf("%d", &newSong->year);
    clearBuffer(); // To consume the newline character

    printf("Lyrics:\n ");
    newSong->lyrics = getName();

    // Set initial streams count
    newSong->streams = 0;
    return newSong;
}

Playlist *addPlayLists( int* counter) {
    Playlist *newplaylist = (Playlist*)malloc(sizeof(Playlist));
    if(newplaylist == NULL) {
    printf("Memory allocation error\n");
        return NULL;
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
char* getName() {
    int len =0;
    char c;
    char* str = (char*)malloc(sizeof(char));
    if (str==NULL) {
        printf("didnt work\n");
        return NULL;
    }
    scanf(" %c",&c);
    while ( c != '\n') {
        *(str+len) = c;
        len++;
        str = (char*)realloc(str, (len + 1) * sizeof(char));
        if (str==NULL) {
            printf("didnt work\n");
            return NULL;
        }
        scanf("%c",&c);
    }
    str[len] = '\0'; // Add null terminator
    return str;
}
void showPlaylist() {

}
void freeSong(Song* song) {
    if (song) {
        free(song->title);
        free(song->artist);
        free(song->lyrics);
        free(song);
    }
}

void freePlaylist(Playlist* playlist) {
    if (playlist) {
        for (int i = 0; i < playlist->songsNum; i++) {
            freeSong(playlist->songs[i]);
        }
        free(playlist->songs);
        free(playlist->name);
        free(playlist);
    }
}
void removePlaylist(Playlist** playlists,int *numPlaylists) {
    if(*numPlaylists == 0) {
        printf("There are no playlists\n");
        return;
    }else {
        printf("Choose a playlist:\n");
        for(int i = 0; i < *numPlaylists; i++) {
            printf("%d. %s\n",i+1,playlists[i]->name);
        }
        printf("%d. Back to main menu\n",*numPlaylists + 1);
        int index;
        do {
            scanf("%d",&index);
            if(index > *numPlaylists || index < 1)
                printf("Invalid option\n");
        }while(index > *numPlaylists || index < 1);
        freePlaylist(playlists[index - 1]);
        for(int i = index - 1; i < *numPlaylists-1; i++) {
            playlists[i] = playlists[i + 1];
        }
        (*numPlaylists)--;
        playlists = (Playlist**)realloc(playlists,*numPlaylists*sizeof(Playlist*));
        printf("Playlist Deleted.\n");
        if(!playlists) {
            return;
        }
    }
}
