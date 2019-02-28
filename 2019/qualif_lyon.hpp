#ifndef QUALIF_LYON_HPP_INCLUDED
#define QUALIF_LYON_HPP_INCLUDED

#include <vector>
#include <string>

struct Photo{
	char v_or_h;
	int nb_tags;
	std::vector<std::string> tags;
	int index;
};

struct Slide{
	Photo* left;
	Photo* right;
	
	Slide(){
		left = nullptr;
		right = nullptr;
	}
	
	Slide(Photo* l){
		left = l;
		right = nullptr;
	}
	
	Slide(Photo* l, Photo* r){
		left = l;
		right = r;
	}
};

int costInterSlide(Slide& s1, Slide& s2);


#endif // QUALIF_LYON_HPP_INCLUDED
