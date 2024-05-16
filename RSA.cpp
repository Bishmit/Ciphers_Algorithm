#include<iostream>
#define ll long long
using namespace std;

int gcd_(int a, int b) {
    if (b == 0) return a;
    else return gcd_(b, a % b);
}

ll FastModExp(ll a, ll b, ll m) {
    ll result = 1;  // Initialize result to 1
    while (b > 0) {
        if (b & 1) {
            result = (result * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;  // Shift right by 1 bit to process the next bit
    }
    return result;
}

ll extendedEuclid(ll a, ll b, ll& x, ll& y){
	// ax + by= gcd(a,b) 
	/*
			Given Equation from the Recursive Call:
			From the recursive call extendedGCD(b, a % b, x1, y1), we know that:
			b * x1 + (a % b) * y1 = gcd(b, a % b)
			Since gcd(b, a % b) = gcd(a, b), we can write:
			b * x1 + (a % b) * y1 = gcd(a, b)
			
			Expressing a % b:
			We know that:
			a % b = a - ⌊a / b⌋ * b
			where ⌊a / b⌋ is the integer division of a by b.
			
			Substituting a % b into the Equation:
			Substitute a % b = a - ⌊a / b⌋ * b into the equation:
			b * x1 + (a - ⌊a / b⌋ * b) * y1 = gcd(a, b)
			
			Distributing y1 inside the Parentheses:
			Distribute y1 in the equation:
			b * x1 + a * y1 - ⌊a / b⌋ * b * y1 = gcd(a, b)
			
			Rearranging Terms:
			Group the terms involving b:
			a * y1 + b * x1 - ⌊a / b⌋ * b * y1 = gcd(a, b)
			a * y1 + b * (x1 - ⌊a / b⌋ * y1) = gcd(a, b)
			
			so from this if we compare it with ax + by= gcd(a,b) 
			we get:
				x = y1; 
				y = x1 - (a/b) * y1; 
	*/
	if(b == 0){
		x = 1; 
		y = 0; 
		return a; 
	}
	
	ll x1, y1; 
	ll gcd = extendedEuclid(b, a%b, x1, y1); 
	x = y1; 
	y = x1 - (a/b) * y1; 
	return gcd; 
}

ll modInverse(ll a, ll m){
	ll x, y; 
	ll g = extendedEuclid(a, m, x, y); 
	if(g != 1) return -1; // Inverse doesn't exist 
	else{
		ll res = (x % m + m) % m; 
		return res; 
	}
}

int main() {
    // RSA algorithm
    ll p, q, M, d;
    cout << "Enter P: "; cin >> p;
    cout << "Enter Q: "; cin >> q;
    cout << "Enter M: "; cin >> M;
    
    // Calculate n
    ll n = p * q;
    
    // Calculate phi
    ll phi = (p - 1) * (q - 1);
    
    // Find e such that 1 < e < phi and gcd(e, phi) = 1
    ll e = 2;  // Starting with 2
    while (e < phi) {
        if (gcd_(e, phi) == 1) {
            break;
        }
        e++;
    }

    /* Naive approach to find modular multiplicative inverse which take O(n) time
    for (ll i = 0; i < phi; i++) {
        if ((e * i) % phi == 1) {
            d = i;
            break;
        }
    }
	*/
	
     d = modInverse(e, phi); // this approach is better with O(log(max(a,b)) i.e O(log(n))
    						 // comment this and uncomment the naive approach above to check performance in that approach
    // Encryption part
    ll C = FastModExp(M, e, n);
    
    // Decryption part
    ll D = FastModExp(C, d, n);
    
    cout << "The Encrypted value: " << C << "\nThe Decrypted value: " << D << endl;
    
    return 0;
}
