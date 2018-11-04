//queue class for source.cpp
struct coord {
	int x;
	int y;
};

class Queue {
private:
	coord *Q;
	int front, rear, size;

public:
	Queue(int maxSize);
	void insert(coord x, int MSIZE);
	coord remove(int MSIZE);
	bool isEmpty();
	bool isFull(int MSIZE);
};

Queue:: Queue(int maxSize) {
	//initialize an empty queue
	front = 0;
	rear = 0;
	size = 0;
	Q = new coord[maxSize];
	for (int j = 0; j < maxSize; ++j)
	{
		Q[j].x = 0;
		Q[j].y = 0;
	}
}

void Queue:: insert(coord x, int MSIZE) { //(point* x)
	if (!isFull(MSIZE)) {
		rear++;
		size++;
		if (rear == MSIZE)
			rear = 0;
		Q[rear] = x;
	}
}

coord Queue::remove(int MSIZE) {
	if (!isEmpty()) {
		front++;
		if (front == MSIZE)
			front = 0;
		size--;
		return Q[front];
	}
}
bool Queue::isEmpty() {
	return (size == 0);
}

bool Queue::isFull(int MSIZE) {
	return (size == MSIZE);
}
