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
void addPlaylist();
void removePlaylist();
void showPlaylists();
void addSong();
void deleteSong();
void sortSongs();
void playSongs();
void addPlayLists(Playlist** playlists);

//some recommendations for functions, you may implement however you want

void deleteSong() {

    printf("Song deleted successfully.\n");
}



void playSong() {
    
}



void freeSong() {

}

void freePlaylist(P) {
    
}

void printPlaylistsMenu() {
    printf("Please Choose:\n"); 
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");   
}



void sortPlaylist() {
    
    printf("sorted\n");
}



int main() {
    Playlist** playlists = NULL;
    mainMinu(&playlists);
}
void mainMinu(Playlist** playlists) {
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
                case 1: {
                    watchPlayslists(&playlists);
                    break;
                }
                case 2: {
                    addPlayLists(&playlists);
                    break;
                }
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

void watchPlayslists(Playlist* header) {
    printf("Choose a playlist:\n");
    Playlist* newPlaylist = header;
    for(int i = 0)

}
void addPlaylist(Playlist* playlists) {}
Playlist *addPlayLists(Playlist* playlists) {
    Playlist *newplaylist = (Playlist*)malloc(sizeof(Playlist));
    if(newplaylist == NULL) {
        exit(1);
    }
    char name[];
    printf("Enter playlist's name:\n");
    scanf(" %s", name);
    newplaylist->name =(char*)malloc(strlen(name) + 1);
    newplaylist->songs = NULL;
    newplaylist->songsNum = ZERO;
    return newplaylist;
}
