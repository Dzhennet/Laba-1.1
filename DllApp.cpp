// DllApp.cpp : Определяет экспортируемые функции для DLL.
//

#include "framework.h"
#include "DllApp.h"
#include <stdexcept>
#include <limits>
#include <iostream>


vector<Post*> vec;
vector<string*> posts;
void clearPosts() {
	for (auto it : posts) {
		delete it;
	}
	posts.clear();
}

void fillPosts() {
	for (auto it : vec)
		posts.push_back(new string((*it).to_str(false)));
}


DLLAPP_API void initData() {
	ifstream file("posts.txt");
	string post;
	while (getline(file, post)) {
		auto it = post.find("$");
		int id = stoi(post.substr(0, it));
		post.erase(0, it + 1);
		vec.push_back(new Post(post, id));
	}
	file.close();
}

DLLAPP_API const vector<string*>& getPosts() {
	clearPosts();
	fillPosts();
	return posts;
}

DLLAPP_API const vector<string*>& getSortPosts(bool rev) {
	clearPosts();
	fillPosts();
	if (rev) {
		sort(posts.begin(), posts.end(), [](string* l, string* r) {
			return stoi(l->substr(1, 2)) < stoi(r->substr(1,2));
			});
		return posts;
	}
	else {
		sort(posts.begin(), posts.end(), [](string* l, string* r) {
			return stoi(l->substr(1, 2)) < stoi(r->substr(1, 2));
			});
		reverse(posts.begin(), posts.end());
		return posts;
	}
}

DLLAPP_API const vector<string*>& getFindPosts(string& right) {
	SubPost* a = new SubPost(right, 1);
	clearPosts();
	auto it = vec.begin();
	while (it != vec.end()) {
			it = find_if(it + 1, vec.end(), [&](Post* r) {
				return *a == *r;
				});
			if (it != vec.end())
				posts.push_back(new string((*it)->to_str(false)));
	}
	delete a;
	return posts;
}

DLLAPP_API void addPost(string& post, int id) {
	vec.push_back(new Post(post, id));
	ofstream file("posts.txt", ios_base::app);
	file << vec.back()->to_str(true) << "\n";
	file.close();
	or NO close
}

DLLAPP_API void deletePost(string& post) {
	SubPost* a = new SubPost(post, 1);
	auto it = std::find_if(vec.begin(), vec.end(), [&](Post* r) {
		return *a == *r;
	});
	if (it != vec.end()){
		delete *it;
		vec.erase(it);
	}
	delete a;
	std::ofstream file("posts.txt", std::ios_base::out | std::ios_base::trunc);
	for (int i = 0; i < vec.size(); i++) {
		 file << vec[i]->to_str(true) + "\n";
	}
	file.close();
}

DLLAPP_API void deleteAll() {
	for (auto it : vec)
		delete it;
	
}
set<Post*> HistoryDB, DiffDB;
DLLAPP_API void setDiff() {

	set_difference(HistoryDB.begin(), HistoryDB.end(), posts.begin(), posts.end(), inserter(DiffDB, DiffDB.begin()));
}

DLLAPP_API void range_word(std::string word)
{
	auto index = equal_range(vec.begin(), vec.end(), word);

}

