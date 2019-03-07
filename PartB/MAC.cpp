#include "MAC.h"

MAC::MAC(){
    musicAlbums = NULL;
    noOfMusicAlbums = 0;
}

MAC::~MAC(){
    if (musicAlbums){
        delete [] musicAlbums;
    }
}

MAC::MAC(const MAC &macToCopy){
    if (macToCopy.noOfMusicAlbums > 0) {
        noOfMusicAlbums = macToCopy.noOfMusicAlbums;
        musicAlbums = new MusicAlbum[noOfMusicAlbums];

        for (int i = 0; i < noOfMusicAlbums; i++) {
            musicAlbums[i] = macToCopy.musicAlbums[i];
        }
    }
    else {
        noOfMusicAlbums = 0;
        musicAlbums = NULL;
    }
}

void MAC::operator=(const MAC &right){
    if ( &right != this ) {
        if (noOfMusicAlbums != right.noOfMusicAlbums) {
            if (noOfMusicAlbums > 0)
                delete [] musicAlbums;
            noOfMusicAlbums = right.noOfMusicAlbums;
            if(noOfMusicAlbums > 0)
                musicAlbums = new MusicAlbum[noOfMusicAlbums];
            else {
                musicAlbums = NULL;
                noOfMusicAlbums = 0;
            }
        }
        for (int i = 0; i < noOfMusicAlbums; i++)
            musicAlbums[i] = right.musicAlbums[i];
    }
}

bool MAC::addMusicAlbum(const string maArtist,
                        const string maTitle,
                        const int maYear){
    if ( noOfMusicAlbums > 0) {
        for (int i = 0; i < noOfMusicAlbums; i++) {
            if ((musicAlbums[i].getMusicAlbumArtist() == maArtist)&&
                (musicAlbums[i].getMusicAlbumTitle() == maTitle) &&
                (musicAlbums[i].getMusicAlbumYear() == maYear) )
                return false;
        }
        MusicAlbum *temp;
        temp = musicAlbums;
        musicAlbums = new MusicAlbum[noOfMusicAlbums + 1];
        for (int i = 0; i < noOfMusicAlbums; i++) {
            musicAlbums[i] = temp[i];
        }
        musicAlbums[noOfMusicAlbums] = MusicAlbum(maArtist, maTitle, maYear);
        noOfMusicAlbums++;
        delete [] temp;
        return true;
    }
    else {
        musicAlbums = new MusicAlbum[1];
        noOfMusicAlbums = 1;
        musicAlbums[0] = MusicAlbum(maArtist, maTitle, maYear);
        return true;
    }
}

bool MAC::removeMusicAlbum(const string maArtist,
                           const string maTitle){
    if ( noOfMusicAlbums > 0) {
        int index = -1;
        for (int i = 0; i < noOfMusicAlbums; i++) {
            if ((musicAlbums[i].getMusicAlbumArtist() == maArtist)&&
                (musicAlbums[i].getMusicAlbumTitle() == maTitle)){
                index = i;
                i = noOfMusicAlbums;
            }
        }
        if ( index < 0)
            return false;

        if (noOfMusicAlbums > 1) {
            MusicAlbum *temp;
            temp = musicAlbums;
            musicAlbums = new MusicAlbum[noOfMusicAlbums - 1];
            for (int i = 0; i < index; i++) {
                musicAlbums[i] = temp[i];
            }
            for (int i = index + 1; i < noOfMusicAlbums; i++) {
                musicAlbums[i-1] = temp[i];
            }
            delete [] temp;
        }
        else {
            delete [] musicAlbums;
            musicAlbums = NULL;
        }
        noOfMusicAlbums--;
        return true;
    }
    else
        return false;
}

int MAC::getMusicAlbums(MusicAlbum *&allMusicAlbums){
    if (noOfMusicAlbums > 0) {
        allMusicAlbums = new MusicAlbum[noOfMusicAlbums];
        for (int i = 0; i < noOfMusicAlbums; i++) {
            allMusicAlbums[i] = musicAlbums[i];
        }
    }
    else
        allMusicAlbums = NULL;
    return noOfMusicAlbums;
}


bool MAC::addSong(const string maArtist, const string maTitle,
                  const string sName, const int sMins,
                  const int sSecs){
    if ( noOfMusicAlbums > 0) {
        int indexAlbum = -1;
        for (int i = 0; i < noOfMusicAlbums; i++) {
            if ((musicAlbums[i].getMusicAlbumArtist() == maArtist)&&
                (musicAlbums[i].getMusicAlbumTitle() == maTitle)) {
                indexAlbum = i;
                i = noOfMusicAlbums;
            }
        }
        if ( indexAlbum < 0) {
            return false;
        }
        return musicAlbums[indexAlbum].addSongToMusicAlbum(sName, sMins, sSecs);
    }
    return false;
}


bool MAC::removeSongs(const string maArtist,
                      const string maTitle){
    if ( noOfMusicAlbums > 0) {
        int indexAlbum = -1;
        for (int i = 0; i < noOfMusicAlbums; i++) {
            if ((musicAlbums[i].getMusicAlbumArtist() == maArtist)&&
                (musicAlbums[i].getMusicAlbumTitle() == maTitle)) {
                indexAlbum = i;
                i = noOfMusicAlbums;
            }
        }
        if ( indexAlbum < 0)
            return false;
        return musicAlbums[indexAlbum].removeAllSongs();
    }
    return false;
}

void MAC::calculateAvgMusicAlbumLength(int &minutes,
                                       int &seconds){
    minutes = 0;
    seconds = 0;
    if (noOfMusicAlbums > 0) {
        int tempMin;
        int tempSec;
        for (int i = 0; i < noOfMusicAlbums; i++) {
            musicAlbums[i].calculateMusicAlbumLength(tempMin, tempSec);
            minutes = minutes + tempMin;
            seconds = seconds + tempSec;
        }
        seconds = seconds + 60*minutes;
        seconds = seconds/noOfMusicAlbums;
        minutes = seconds/60;
        seconds = seconds % 60;
    }
}
