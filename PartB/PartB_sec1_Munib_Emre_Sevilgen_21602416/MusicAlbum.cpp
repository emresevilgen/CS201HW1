#include "MusicAlbum.h"

MusicAlbum::MusicAlbum(const string maArtist,
                       const string maTitle,
                       const int maYear){
    artist = maArtist;
    title = maTitle;
    year = maYear;
    songs = NULL;
    noSongs = 0;
}

MusicAlbum::~MusicAlbum(){
    if (songs)
        delete [] songs;
}

MusicAlbum::MusicAlbum(const MusicAlbum &maToCopy){
    artist = maToCopy.artist;
    title = maToCopy.title;
    year = maToCopy.year;
    if (maToCopy.noSongs > 0) {
        noSongs = maToCopy.noSongs;
        songs = new Song[noSongs];

        for (int i = 0; i < noSongs; i++) {
            songs[i] = maToCopy.songs[i];
        }
    }
    else {
        noSongs = 0;
        songs = NULL;
    }

}

void MusicAlbum::operator=(const MusicAlbum &right){
    if ( &right != this ) {
        artist = right.artist;
        title = right.title;
        year = right.year;

        if (noSongs != right.noSongs) {
            if (noSongs > 0)
                delete [] songs;
            noSongs = right.noSongs;
            if(noSongs > 0)
                songs = new Song[noSongs];
            else {
                songs = NULL;
                noSongs = 0;
            }
        }
        for (int i = 0; i < noSongs; i++)
            songs [i] = right.songs[i];
    }
}

string MusicAlbum::getMusicAlbumArtist(){
    return artist;
}

string MusicAlbum::getMusicAlbumTitle(){
    return title;
}

int MusicAlbum::getMusicAlbumYear(){
    return year;
}

void MusicAlbum::calculateMusicAlbumLength(int &minutes, int &seconds){
    minutes = 0;
    seconds = 0;
    if (noSongs > 0) {
        for (int i = 0; i < noSongs; i++) {
            minutes = minutes + songs[i].getSongMins();
            seconds = seconds + songs[i].getSongSecs();
        }
        minutes = minutes + (seconds / 60);
        seconds = (seconds % 60);
    }
}

bool MusicAlbum::addSongToMusicAlbum(const string sName,
                                     const int sMins,
                                     const int sSecs){
    if ( noSongs > 0) {
        for (int i = 0; i < noSongs; i++) {
            if ((songs[i].getSongName() == sName)&&
                (songs[i].getSongMins() == sMins)&&
                (songs[i].getSongSecs() == sSecs) )
                return false;
        }
        Song *temp;
        temp = songs;
        songs = new Song[noSongs + 1];
        for (int i = 0; i < noSongs; i++) {
            songs[i] = temp[i];
        }
        songs[noSongs] = Song(sName, sMins, sSecs);
        noSongs++;
        delete [] temp;
        return true;
    }
    else {
        songs = new Song[1];
        noSongs = 1;
        songs[0] = Song(sName, sMins, sSecs);
        return true;
    }
}

bool MusicAlbum::removeAllSongs(){
    if (noSongs > 0) {
        delete [] songs;
        songs = NULL;
        noSongs = 0;
        return true;
    }
    return false;
}
