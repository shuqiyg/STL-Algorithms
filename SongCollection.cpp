/* Workshop 7 - STL Algorithms
   Name: Shuqi Yang
   Std ID: 132162207
   Email: syang136@myseneca.ca
   Date: 07-15-2021
   -------------------------------------------------------
   I have done all the coding by myself and only copied the
   code that my professor provided to complete my workshops
   and assignments.
 */
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <vector>
#include <list>
#include <iomanip>
#include <functional>
#include "SongCollection.h"

namespace sdds {
	SongCollection::SongCollection(const char* filename) {
		std::ifstream fileobj(filename);
		if (!fileobj) throw std::string("Invalid filename");
		std::string song_record;
		while (!fileobj.eof()) {
			if (fileobj)
				getline(fileobj, song_record);
			numOfSongs++;
		}
		fileobj.clear();
		fileobj.seekg(0);
		size_t count = 0;
		while (!fileobj.eof() && count < numOfSongs) {
			std::getline(fileobj, song_record);
			Song sg{};
			size_t next_pos = 0; 
			//title
			sg.title = song_record.substr(next_pos, 25);
			size_t start_pos = sg.title.find_first_not_of(' ');
			size_t end_pos = sg.title.find_last_not_of(' ');
			sg.title = sg.title.substr(start_pos, end_pos - start_pos + 1);
			//artist
			next_pos += 25;
			sg.artist = song_record.substr(next_pos, 25);
			start_pos = sg.artist.find_first_not_of(' ');
			end_pos = sg.artist.find_last_not_of(' ');
			sg.artist = sg.artist.substr(start_pos, end_pos - start_pos + 1);
			//album
			next_pos += 25;
			sg.album = song_record.substr(next_pos, 25);
			start_pos = sg.album.find_first_not_of(' ');
			end_pos = sg.album.find_last_not_of(' ');
			sg.album = sg.album.substr(start_pos, end_pos - start_pos + 1);
			//year
			next_pos += 25;
			sg.release_year = song_record.substr(next_pos, 5);
			start_pos = sg.release_year.find_first_not_of(' ');
			end_pos = sg.release_year.find_last_not_of(' ');
			if (start_pos >= end_pos) {
				sg.release_year = "";
			}else{
				sg.release_year = sg.release_year.substr(start_pos, end_pos - start_pos + 1);
			}
			//length
			next_pos += 5;
			std::string lg_string;
			lg_string = song_record.substr(next_pos, 5);
			start_pos = lg_string.find_first_not_of(' ');
			end_pos = lg_string.find_last_not_of(' ');
			lg_string = lg_string.substr(start_pos, end_pos - start_pos + 1);
			sg.length_song = std::stoi(lg_string);
			//price
			std::string pr_string;
			next_pos += 5;
			pr_string = song_record.substr(next_pos, 5);
			sg.m_price = std::stod(pr_string);
			songs.push_back(sg);
			count++; // next record
		}
	}
	void SongCollection::sort(const char* field) {
		std::string str(field);
		std::sort(songs.begin(), songs.end(), [=](Song& song1, Song& song2) {
			bool compare{};
			if (str == "title") {
				compare = song1.title < song2.title;
			};
			if (str == "album") {
				compare = song1.album < song2.album;
			}
			if (str == "length") {
				compare = song1.length_song < song2.length_song;
			}
			return compare;
			});
	}
	void SongCollection::cleanAlbum() {
		std::for_each(songs.begin(), songs.end(), [](Song& song) {if (song.album == "[None]") {
			song.album = "\0";
			}
		});
	}
	bool SongCollection::inCollection(const char* artist) const {
		return std::any_of(songs.begin(), songs.end(), [&](Song song) {
			return song.artist == artist;
			});
	}
	std::list<Song> SongCollection::getSongsForArtist(const char* artist) const {
		size_t songs_count = std::count_if(songs.begin(), songs.end(), [&](Song song) {return song.artist == artist; });
		std::list<Song> song_list(songs_count);
		std::copy_if(songs.begin(), songs.end(), song_list.begin(), [&](Song song) {return song.artist == std::string(artist); });
		return song_list;
	}
	void SongCollection::display(std::ostream& out) const {
		size_t total_playtime;
		std::for_each(songs.begin(), songs.end(), [&](Song song) { out << song << std::endl; });
		std::vector<size_t> playtime_list(numOfSongs);
		std::transform(songs.begin(), songs.end(), playtime_list.begin(), [](Song song) { return song.length_song;  });
		total_playtime = std::accumulate(playtime_list.begin(), playtime_list.end(), (size_t)0);
		out << std::setw(89) << std::setfill('-') << '\n' << std::setfill(' ');
		out << "| " << std::right << std::setw(77) << "Total Listening Time: ";
		size_t seconds, minutes, hours;
		hours = total_playtime / 60 / 60;
		minutes = (total_playtime % (60 * 60) / 60);
		seconds = total_playtime % (60 * 60) - minutes * 60;
		out << hours <<":" <<minutes << ":" << seconds <<" |" << std::endl;
	}
	std::ostream& operator << (std::ostream& out, const Song& theSong) {
		out << "| " << std::left << std::setw(20) << theSong.title << " | " << std::setw(15) << theSong.artist << " | " << std::setw(20) << theSong.album << " | " << std::right << std::setw(6) << theSong.release_year << " | ";
		size_t seconds, minutes;
		seconds = theSong.length_song;
		minutes = seconds / 60;
		seconds = seconds % 60;
		out << minutes << ":" << std::setw(2) << std::setfill('0') << seconds << std::setfill(' ') << " | " << theSong.m_price << " |";
		return out;
	};
}
