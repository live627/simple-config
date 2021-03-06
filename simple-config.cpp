// simple-config.cpp : Defines the entry point for the applicatio
//

#include <iostream>
#include <sstream>
#include <conio.h>
#include "simple-config.h"


int main() 
{
	std::istringstream ss(R"(
type             =         7
error
type=9
blank=
=1
[fa]il]
[b[a]d]
[protocol]
version = 6

[user]
  name = Bob Smith
 	 email = bob@smith.com
	active = true

pi = 3.14159


; last modified 1 April 2001 by John Doe
[owner]
name=John Doe
organization=Acme Widgets Inc.

[database]
; use IP address in case network name resolution is not working
server=192.0.2.62     
port : 143
file="payroll.dat"

[user]
id=55
)");
	config cfg(ss); 
	
	std::cout << "Number of sections: " << cfg.GetIniMap().size() << std::endl;
	for (const auto &heading : cfg) {
		std::cout<< "section name: " << heading.first << std::endl;
		std::cout << "Number of items: " << heading.second.size() << std::endl;
		for (const auto &kvs : heading.second) {
			std::cout << "Item (" << kvs.first << "): " << kvs.second << std::endl;
		}
		std::cout << std::endl;
	}
	const auto usersection = cfg.GetSection("user");

	std::cout << "email=" << cfg.GetValue("user", "email") << '\n';

	std::stringstream oss("\nserialize\n\n", std::ios_base::ate | std::ios_base::out);
	cfg << oss;

	std::cout << oss.str();

	getch();
}