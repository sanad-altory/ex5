/******************
Name:SANAD ALTORY
ID:214633703
Assignment:EX5
*******************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ZERO 0
#define ONE 1
#define EXIT 6

// Song struct stores song details.
typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
} Song;

// Playlist struct holds a playlist's name and its songs.
typedef struct Playlist {
    char* name;
    Song** songs;
    int songsNum;
} Playlist;

// Main Menu function, initiates the entire playlist system.
void mainMinu();
// Function to watch, manage, and interact with playlists.
void watchPlayslists(Playlist **playlist, int numPlaylists);
// Frees memory for all playlists and their songs.
void freeAllPlaylists(Playlist** playlists, int numPlaylists);
// Frees memory for an individual playlist and its songs.
void freePlaylist(Playlist* playlist);
// Frees memory for an individual song.
void freeSong(Song* song);
// Removes a playlist and frees its memory.
void removePlaylist(Playlist*** playlists, int *numPlaylists);
// Displays a list of songs in a playlist.
void showPlaylist(Song** songs, int songsNum);
// Creates a new song, collects song details from user.
Song* createSong();
// Adds a new song to a playlist.
void addSong(Playlist* playlist);
// Deletes a song from a playlist.
void deleteSong(Song*** songs, int* songsNum);
// Sorts songs by different criteria.
void sortSongs(Song** songs, int numSongs);
// Plays all songs in the playlist.
void playSongs(Song** songs, int numSongs);
// Adds a new playlist and returns the playlist pointer.
Playlist* addPlayLists(int* counter);
// Reads a string input from the user, dynamically allocating memory.
char* getName();
// Clears the input buffer (for handling newline characters).
void clearBuffer();

int main() {
    mainMinu();
    return ZERO;

}// Main menu where user can choose to manage playlists, add, or delete playlists.
void mainMinu() {
    int numPlaylists = 0;
    int capacity = 1;
    Playlist** playlists = (Playlist**)malloc(sizeof(Playlist*));
    if (!playlists) exit(1);
    int task ;
    while(ONE){
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
                        // Memory allocation failed: exit the program
                        if(!playlists) {
                            freeAllPlaylists(playlists, numPlaylists);
                            exit(1);
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
    while (ONE) {
        // Keep looping to allow returning to the playlist menu
        printf("Choose a playlist:\n");
        for (int i = 0; i < numPlaylists; i++) {
            printf("\t%d. %s\n", i + ONE, playlist[i]->name);
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
                    if(playlist[playlistIndex-ONE]->songsNum == ZERO) {
                        printf("choose a song to play, or 0 to quit:\n");
                        scanf("%d", &songToPlay);
                        break;
                    }else {
                        showPlaylist(playlist[playlistIndex-ONE]->songs,playlist[playlistIndex-ONE]->songsNum);
                    }
                    break;
                }//Add Song to the Playlist.
                case 2: {
                    addSong(playlist[playlistIndex-ONE]);
                    break;
                }//Delete a Song from the Playlist.
                case 3: {
                    deleteSong(&playlist[playlistIndex-ONE]->songs,&playlist[playlistIndex-ONE]->songsNum);
                    break;
                }//Sort the Playlist.
                case 4: {
                    sortSongs(playlist[playlistIndex-ONE]->songs,playlist[playlistIndex-ONE]->songsNum);
                    printf("sorted\n");
                    break;
                }//Play all the Songs in the Playlist.
                case 5: {
                    playSongs(playlist[playlistIndex-ONE]->songs,playlist[playlistIndex-ONE]->songsNum);
                    break;
                }
                case 6:{
                    break;
                }
            }
            // Exit the inner loop to show the playlists again
            if (task == EXIT) break;
        }
    }

}// Frees all the playlists and their associated songs.
void freeAllPlaylists(Playlist** playlists, int numPlaylists) {
    for (int i = 0; i < numPlaylists; i++) {
        freePlaylist(playlists[i]);
    }
    free(playlists);
}
// Frees memory for an individual playlist and its songs.
void freePlaylist(Playlist* playlist) {
    if (!playlist) return;
    free(playlist->name);
    for (int i = 0; i < playlist->songsNum; i++) {
        freeSong(playlist->songs[i]);
    }// Free array of song pointers
    free(playlist->songs);
    free(playlist);
}// Frees memory for a song (title, artist, lyrics, etc.).
void freeSong(Song* song) {
    if (!song) return;

    free(song->title);  // Free song title
    free(song->artist); // Free artist name
    free(song->lyrics); // Free lyrics
    free(song);         // Free song struct
}
// Plays all the songs, displaying song lyrics and increasing streams.
void playSongs(Song **songs,int numSongs) {
    for(int i = 0; i < numSongs; i++) {
        Song* selectedSong = songs[i];
        printf("Now playing %s:\n"
            "$ %s $\n",selectedSong->title,selectedSong->lyrics);
        selectedSong->streams++;
    }
}
// Sorts the songs in different ways based on user input (year, streams, etc.).
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
            for(int i = 0; i < numSongs - ONE; i++) {
                for(int j = i+ONE; j < numSongs; j++) {
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
        case 2: {// Iterate from last to second element
            for (int i = numSongs - ONE; i > ZERO; i--) {
                // Compare each pair of adjacent elements
                for (int j = 0; j < i; j++) {
                    if (songs[j]->streams > songs[j + ONE]->streams) {
                        // Swap the pointers
                        Song* temp = songs[j];
                        songs[j] = songs[j + ONE];
                        songs[j + ONE] = temp;
                    }
                }
            }
            break;
        }// sort by streams - descending order
        case 3: {// Iterate from last to second element
            for (int i = numSongs - ONE; i > ZERO; i--) {
                // Compare each pair of adjacent elements
                for (int j = 0; j < i; j++) {
                    if (songs[j]->streams < songs[j + ONE]->streams) {
                        // Swap the pointers
                        Song* temp = songs[j];
                        songs[j] = songs[j + ONE];
                        songs[j + ONE] = temp;
                    }
                }
            }
            break;
        }// sort alphabetically
        default: {
            for(int i = 0; i < numSongs - ONE; i++) {
                for(int j = i+ONE; j < numSongs; j++) {
                    if(strcmp(songs[i]->title, songs[j]->title) > ZERO) {
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

}// Deletes a song from the playlist after confirming with the user.
void deleteSong(Song*** songs, int* songsNum) {
    if (*songsNum == ZERO) {
        printf("There are no songs to delete.\n");
        return;
    }
    // Display songs
    for (int i = 0; i < *songsNum; i++) {
        printf("%d. Title: %s\n"
               "   Artist: %s\n"
               "   Released: %d\n"
               "   Streams: %d\n",
               i + ONE, (*songs)[i]->title, (*songs)[i]->artist, (*songs)[i]->year, (*songs)[i]->streams);
    }
    printf("choose a song to delete, or 0 to quit:\n");
    int selectedSong;
    scanf("%d", &selectedSong);
    if (selectedSong == ZERO) {
        return; // Exit without deletion
    }
    // Free the selected song
    freeSong((*songs)[selectedSong - ONE]);
    // Shift remaining songs
    for (int i = selectedSong - ONE; i < *songsNum - ONE; i++) {
        (*songs)[i] = (*songs)[i + ONE];
    }
    (*songsNum)--;
    // Reallocate memory
    Song** temp = (Song**)realloc(*songs, *songsNum * sizeof(Song*));
    if (temp == NULL && *songsNum > ZERO) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
    *songs = temp;  // Update the original pointer
    printf("Song deleted successfully.\n");
}
// Displays a list of all songs in a playlist.
void showPlaylist(Song **songs, int songsNum) {
    for (int i = 0; i < songsNum; i++) {
        printf("%d. Title: %s\n"
            " Artist: %s\n"
            " Released: %d\n"
            " Streams: %d\n",i+ONE,songs[i]->title,songs[i]->artist,songs[i]->year,songs[i]->streams);
    }
    while(ONE) {
        printf("choose a song to play, or 0 to quit:\n");
        int songToPlay;
        scanf("%d", &songToPlay);
        if(songToPlay != ZERO){
            Song* selectedSong = songs[songToPlay-ONE];
            printf("Now playing %s:\n"
                "$ %s $\n",selectedSong->title,selectedSong->lyrics);
            selectedSong->streams++;
        }else
            return;
    }
}// Function to add a song to a playlist.
void addSong(Playlist *playlist) {
    Song* newSong = createSong();
    playlist->songsNum++;
    playlist->songs = (Song**)realloc(playlist->songs,playlist->songsNum*sizeof(Song*));
    if (!playlist->songs) {
        free(newSong);  // Free newly allocated song
        exit(1);  // Critical error: exit the program
    }
    playlist->songs[playlist->songsNum-ONE] = newSong;
}// Function to create a new song by asking user for details.
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
    // To consume the newline character
    clearBuffer();
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
}// Clears the input buffer.
void clearBuffer() {
    while (getchar() != '\n');
}
// Function to dynamically get a song title, artist, or lyrics.
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
        str = (char*)realloc(str, (len + ONE) * sizeof(char));
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
        printf("%d. %s\n", i + ONE, (*playlists)[i]->name);
    }
    printf("%d. Back to main menu\n", *numPlaylists + ONE);
    int index;
    scanf("%d", &index);
    if (index < ONE || index > *numPlaylists) {
        return; // Invalid index, return to main menu
    }
    // Free the selected playlist
    freePlaylist((*playlists)[index - ONE]);
    // Shift remaining playlists
    for (int i = index - ONE; i < *numPlaylists - ONE; i++) {
        (*playlists)[i] = (*playlists)[i + ONE];
    }
    (*numPlaylists)--;
    // Reallocate memory for the playlists array
    Playlist** temp = (Playlist**)realloc(*playlists, *numPlaylists * sizeof(Playlist*));
    if (temp == NULL && *numPlaylists > ZERO) {
        printf("Memory reallocation failed\n");
        return; // Exit safely without modifying the original pointer
    }
    *playlists = temp;
    printf("Playlist deleted.\n");
}


