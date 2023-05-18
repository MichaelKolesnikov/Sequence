#pragma once

#include "Stack.h"

class Ring {
private:
	int radius;
	int color;
public:
	Ring() : radius(1), color(0) {}
	Ring(int radius, int color) : radius(radius), color(color) {}

	int get_color() const {
		return this->color;
	}

	int get_radius() const {
		return this->radius;
	}

	friend std::ostream& operator<< (std::ostream& stream, const Ring& ring) {
		stream << "Ring(" << ring.get_radius() << ", " << ring.get_color() << ")";
		return stream;
	}
};

class HanoiTowers {
private:
	int start;
	int target;
	int n;
	ArraySequence<Stack<Ring>> rod = ArraySequence<Stack<Ring>>((size_t)3);
public:
	HanoiTowers(ArraySequence<Ring>& items, size_t start, size_t target) : start(start), target(target), n(items.get_length()) {
		if (!(0 <= start <= 2)) {
			throw "Wrong start (only 0, 1, 2 can be correct)";
		}
		if (!(0 <= target <= 2)) {
			throw "Wrong target (only 0, 1, 2 can be correct)";
		}
		for (size_t i = 0; i < items.get_length(); ++i) {
			rod[start].push(items.get(i));
		}
	}

	int get_start() const {
		return this->start;
	}

	int get_target() const {
		return this->target;
	}

	size_t get_n() const {
		return this->n;
	}

	bool win() const {
		return this->rod.get(this->get_target()).get_size() == this->get_n();
	}

	bool move(size_t sourse, size_t destination) {
		if (!(0 <= sourse <= 2)) {
			throw "Wrong sourse (only 0, 1, 2 can be correct)";
		}
		if (!(0 <= destination <= 2)) {
			throw "Wrong destination (only 0, 1, 2 can be correct)";
		}

		if (this->rod[sourse].is_empty() || 
			(!(this->rod[destination].is_empty()) && this->rod[destination].peek().get_radius() < this->rod[sourse].peek().get_radius()))
		{
			return false;
		}
		Ring ring = rod[sourse].pop();
		rod[destination].push(ring);
		return true;
	}

	friend std::ostream& operator<< (std::ostream& stream, const HanoiTowers& Hanoi_towers) {
		stream << std::endl;
		stream << "0: ";
		stream << Hanoi_towers.rod.get(0);
		stream << "1: ";
		stream << Hanoi_towers.rod.get(1);
		stream << "2: ";
		stream << Hanoi_towers.rod.get(2);
		stream << std::endl;
		return stream;
	}
};

void make_solution(size_t n, size_t start, size_t target, ArraySequence<ArraySequence<size_t>*>& solution) {
	if (n > 0) {
		size_t tmp = 3 - start - target;
		make_solution(n - 1, start, tmp, solution);
		solution.append(new ArraySequence<size_t>(new size_t[]{ start, target }, 2));
		make_solution(n - 1, tmp, target, solution);
	}
}

void solve_Hanoi_towers(HanoiTowers& Hanoi_towers) {
	ArraySequence<ArraySequence<size_t>*> solution = ArraySequence<ArraySequence<size_t>*>();
	make_solution(Hanoi_towers.get_n(), Hanoi_towers.get_start(), Hanoi_towers.get_target(), solution);
	/*for (IConstIterator<ArraySequence<size_t>*>* it = solution->Icbegin(); !(it->is_equal(solution->Icend())); it->next()) {
		cout << Hanoi_towers.move(
			it->get()->get(0),
			it->get()->get(1)
		);
	}*/
	// cout << Hanoi_towers;
	for (int i = 0; i < solution.get_length(); ++i) {
		Hanoi_towers.move(solution.get(i)->get(0), solution.get(i)->get(1));
	}
}
