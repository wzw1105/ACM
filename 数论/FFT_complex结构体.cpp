struct complex{
	double r,i;
	complex(double a=0.0,double b=0.0){
		r=a;i=b;
	}
	double real() const{return r;}
	double imag() const{return i;}

	complex& operator=(const complex& other){
		this->r=other.r;
		this->i=other.i;
		return *this;
	}
	friend complex operator*(complex a,const complex& b){
		return a *= b;
	}
	complex& operator*=(const complex other){
		double memor_r=this->r,memor_i=this->i;
		this->r=((memor_r*other.r)-(memor_i*other.i));
		this->i=((memor_i*other.r)+(memor_r*other.i));
		return *this;
	}
	friend complex operator+(complex a,const complex& b){
		return a += b;
	}
	complex& operator+=(const complex& other){
		this->r+=other.r;
		this->i+=other.i;
		return *this;
	}
	friend complex operator-(complex a,const complex& b){
		return a -= b;
	}
	complex& operator-=(const complex& other){
		this->r-=other.r;
		this->i-=other.i;
		return *this;
	}
	friend complex operator/(complex a,const int b){
		return a /= b;
	}
	complex& operator/=(const int k){
		this->r/=(double)k;
		this->i/=(double)k;
		return *this;
	}
};
