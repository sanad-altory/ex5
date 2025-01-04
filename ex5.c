#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ZERO 0
#define ONE 1
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
void mainMinu(); // ready
void watchPlayslists(Playlist **playlist,int numPlaylists); // ready
void freeAllPlaylists(Playlist** playlists, int numPlaylists);
void freePlaylist(Playlist* playlist); // ready
void freeSong(Song* song); // ready
void removePlaylist(Playlist*** playlists,int *numPlaylists); //ready
void showPlaylist(Song** songs, int songsNum); // ready
Song* createSong(); // ready
void addSong(Playlist* playlist); //ready
void deleteSong(Song*** songs, int* songsNum); // ready
void sortSongs(Song** songs, int numSongs); // ready
void playSongs(Song** songs, int numSongs); // ready
Playlist *addPlayLists(int* counter);//ready
char* getName(); //ready
void clearBuffer();// ready

int main() {
    mainMinu();
    return 0;

}
void mainMinu() {
    int numPlaylists = 0;
    int capacity = 1;
    Playlist** playlists = (Playlist**)malloc(sizeof(Playlist*));
    if (!playlists) exit(1);
    int task ;
    while(1){
        printf("Please Choose:\n"
            "\t1. Watch playlists\n"
            "\t2. Add playlist\n"
            "\t3. Remove playlist\n"
            "\t4. exit\n");
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
                        if(!playlists) {
                            freeAllPlaylists(playlists, numPlaylists);
                            exit(1);// Memory allocation failed: exit the program
                        }
                    }
                    playlists[numPlaylists]=addPlayLists(&numPlaylists);

                    break;
                }//Remove Playlist
                case 3: {
                    removePlaylist(&playlists,&numPlaylists);
                    clearBuffer();
                    break;
                }
                case 4: {
                    printf("Goodbye!\n");
                    freeAllPlaylists(playlists, numPlaylists);
                    return;
                }
                default:
                    printf("Invalid option\n");
            }
        }
    }

void watchPlayslists(Playlist **playlist,int numPlaylists) {
    while (1) {
        // Keep looping to allow returning to the playlist menu
        printf("Choose a playlist:\n");
        for (int i = 0; i < numPlaylists; i++) {
            printf("\t%d. %s\n", i + 1, playlist[i]->name);
        }
        printf("\t%d. Back to main menu\n", numPlaylists + ONE);
        int playlistIndex;
        scanf("%d", &playlistIndex);

        // Handle "Back to main menu" option
        if (playlistIndex == numPlaylists + ONE) {
            return; // Exit to the main menu
        }
        int task;
        printf("playlist %s:\n",playlist[playlistIndex-ONE]->name);
        while(ONE) {
            printf("\t1. Show Playlist\n"
                "\t2. Add Song\n"
                "\t3. Delete Song\n"
                "\t4. Sort\n"
                "\t5. Play\n"
                "\t6. exit\n");
            scanf("%d",&task);
            switch(task) {
                //Show the Playlist.
                case 1: {
                    int songToPlay;
                    if(playlist[playlistIndex-ONE]->songsNum == 0) {
                        printf("choose a song to play, or 0 to quit:\n");
                        scanf("%d", &songToPlay);
                        break;
                    }else {
                        showPlaylist(playlist[playlistIndex-1]->songs,playlist[playlistIndex-1]->songsNum);
                    }
                    break;
                }//Add Song to the Playlist.
                case 2: {
                    addSong(playlist[playlistIndex-1]);
                    break;
                }//Delete a Song from the Playlist.
                case 3: {
                    deleteSong(&playlist[playlistIndex-1]->songs,&playlist[playlistIndex-1]->songsNum);
                    break;
                }//Sort the Playlist.
                case 4: {
                    sortSongs(playlist[playlistIndex-1]->songs,playlist[playlistIndex-1]->songsNum);
                    printf("sorted\n");
                    break;
                }//Play all the Songs in the Playlist.
                case 5: {
                    playSongs(playlist[playlistIndex-1]->songs,playlist[playlistIndex-1]->songsNum);
                    break;
                }
                case 6:{
                    break;
                }
            }
            // Exit the inner loop to show the playlists again
            if (task == 6) break;

        }
    }

}
void freeAllPlaylists(Playlist** playlists, int numPlaylists) {
    for (int i = 0; i < numPlaylists; i++) {
        freePlaylist(playlists[i]);
    }
    free(playlists);
}

void freePlaylist(Playlist* playlist) {
    if (!playlist) return;

    free(playlist->name);  // Free playlist name

    for (int i = 0; i < playlist->songsNum; i++) {
        freeSong(playlist->songs[i]);
    }
    free(playlist->songs);  // Free array of song pointers
    free(playlist);         // Free playlist struct
}


void freeSong(Song* song) {
    if (!song) return;

    free(song->title);  // Free song title
    free(song->artist); // Free artist name
    free(song->lyrics); // Free lyrics
    free(song);         // Free song struct
}


void playSongs(Song **songs,int numSongs) {
    for(int i = 0; i < numSongs; i++) {
        Song* selectedSong = songs[i];
        printf("Now playing %s:\n"
            "$ %s $\n",selectedSong->title,selectedSong->lyrics);
        selectedSong->streams++;
    }
}
void sortSongs(Song **songs,int numSongs) {
    printf("choose:\n"
        "1. sort by year\n"
        "2. sort by streams - ascending order\n"
        "3. sort by streams - descending order\n"
        "4. sort alphabetically\n");
    int sortWay;
    scanf("%d",&sortWay);
    switch(sortWay) {
        // sort by year
        case 1: {
            for(int i = 0; i < numSongs - 1; i++) {
                for(int j = i+1; j < numSongs; j++) {
                    if(songs[i]->year > songs[j]->year) {
                        // swap the pointers
                        Song* songSorter = songs[i];
                        songs[i] = songs[j];
                        songs[j] = songSorter;
                    }
                }
            }
            break;
        }// sort by streams - ascending order
        case 2: {
            for (int i = numSongs - 1; i > 0; i--) { // Iterate from last to second element
                for (int j = 0; j < i; j++) {       // Compare each pair of adjacent elements
                    if (songs[j]->streams > songs[j + 1]->streams) {
                        // Swap the pointers
                        Song* temp = songs[j];
                        songs[j] = songs[j + 1];
                        songs[j + 1] = temp;
                    }
                }
            }
            break;
        }// sort by streams - descending order
        case 3: {
            for (int i = numSongs - 1; i > 0; i--) { // Iterate from last to second element
                for (int j = 0; j < i; j++) {       // Compare each pair of adjacent elements
                    if (songs[j]->streams < songs[j + 1]->streams) {
                        // Swap the pointers
                        Song* temp = songs[j];
                        songs[j] = songs[j + 1];
                        songs[j + 1] = temp;
                    }
                }
            }
            break;
        }// sort alphabetically
        default: {
            for(int i = 0; i < numSongs - 1; i++) {
                for(int j = i+1; j < numSongs; j++) {
                    if(strcmp(songs[i]->title, songs[j]->title) > 0) {
                        // swap the pointers
                        Song* songSorter = songs[i];
                        songs[i] = songs[j];
                        songs[j] = songSorter;
                    }
                }
            }
            break;
        }
    }

}
void deleteSong(Song*** songs, int* songsNum) {
    if (*songsNum == 0) {
        printf("There are no songs to delete.\n");
        return;
    }

    // Display songs
    for (int i = 0; i < *songsNum; i++) {
        printf("%d. Title: %s\n"
               "   Artist: %s\n"
               "   Released: %d\n"
               "   Streams: %d\n",
               i + 1, (*songs)[i]->title, (*songs)[i]->artist, (*songs)[i]->year, (*songs)[i]->streams);
    }

    printf("choose a song to delete, or 0 to quit:\n");
    int selectedSong;
    scanf("%d", &selectedSong);

    if (selectedSong == 0) {
        return; // Exit without deletion
    }

    // Free the selected song
    freeSong((*songs)[selectedSong - 1]);

    // Shift remaining songs
    for (int i = selectedSong - 1; i < *songsNum - 1; i++) {
        (*songs)[i] = (*songs)[i + 1];
    }
    (*songsNum)--;

    // Reallocate memory
    Song** temp = (Song**)realloc(*songs, *songsNum * sizeof(Song*));
    if (temp == NULL && *songsNum > 0) {
        printf("Memory reallocation failed\n");
        exit(1);
    }

    *songs = temp;  // Update the original pointer

    printf("Song deleted successfully.\n");
}


void showPlaylist(Song **songs, int songsNum) {
    for (int i = 0; i < songsNum; i++) {
        printf("%d. Title: %s\n"
            " Artist: %s\n"
            " Released: %d\n"
            " Streams: %d\n",i+1,songs[i]->title,songs[i]->artist,songs[i]->year,songs[i]->streams);
    }
    while(ONE) {
        printf("choose a song to play, or 0 to quit:\n");
        int songToPlay;
        scanf("%d", &songToPlay);
        if(songToPlay != ZERO){
            Song* selectedSong = songs[songToPlay-1];
            printf("Now playing %s:\n"
                "$ %s $\n",selectedSong->title,selectedSong->lyrics);
            selectedSong->streams++;
        }else
            return;
    }
}
void addSong(Playlist *playlist) {
    Song* newSong = createSong();
    playlist->songsNum++;
    playlist->songs = (Song**)realloc(playlist->songs,playlist->songsNum*sizeof(Song*));
    if (!playlist->songs) {
        free(newSong);  // Free newly allocated song
        exit(1);  // Critical error: exit the program
    }
    playlist->songs[playlist->songsNum-1] = newSong;
}
Song* createSong() {
    Song* newSong = (Song*)malloc(sizeof(Song));
    if(!newSong) {
        free(newSong);
        exit(1);
    }
    // Collect song details
    printf("Enter song's details\n");

    printf("Title:\n");
    newSong->title = getName();
    printf("Artist:\n");
    newSong->artist = getName();

    printf("Year of release:\n");
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
    if(!newplaylist ) {
    printf("Memory allocation error\n");
        free(newplaylist);
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
    while (getchar() != '\n'); // Clear until newline
}
// function to allocate unlimited string and return a pointer to it.
char* getName() {
    int len =0;
    char c;
    char* str = (char*)malloc(sizeof(char));
    if (!str) {
        printf("didnt work\n");
        free(str); // Free original memory before returning NULL
        exit(1);
    }
    scanf(" %c",&c);
    while ( c != '\n' && c != '\r') {
        *(str+len) = c;
        len++;
        str = (char*)realloc(str, (len + 1) * sizeof(char));
        if (str==NULL) {
            printf("didnt work\n");
            free(str); // Free original memory before returning NULL
            exit(1);
        }
        scanf("%c",&c);
    }
    str[len] = '\0'; // Add null terminator
    return str;
}

void removePlaylist(Playlist*** playlists, int* numPlaylists) {
    printf("Choose a playlist:\n");
    for (int i = 0; i < *numPlaylists; i++) {
        printf("%d. %s\n", i + 1, (*playlists)[i]->name);
    }
    printf("%d. Back to main menu\n", *numPlaylists + 1);

    int index;
    scanf("%d", &index);
    if (index < 1 || index > *numPlaylists) {
        return; // Invalid index, return to main menu
    }

    // Free the selected playlist
    freePlaylist((*playlists)[index - 1]);

    // Shift remaining playlists
    for (int i = index - 1; i < *numPlaylists - 1; i++) {
        (*playlists)[i] = (*playlists)[i + 1];
    }
    (*numPlaylists)--;

    // Reallocate memory for the playlists array
    Playlist** temp = (Playlist**)realloc(*playlists, *numPlaylists * sizeof(Playlist*));
    if (temp == NULL && *numPlaylists > 0) {
        printf("Memory reallocation failed\n");
        return; // Exit safely without modifying the original pointer
    }
    *playlists = temp;

    printf("Playlist deleted.\n");
}


