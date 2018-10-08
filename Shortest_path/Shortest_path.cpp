// K_shortest_path.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <string>
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

#define MAX_DISTANCE 1000

int _tmain(int argc, _TCHAR* argv[])
{
	map<string,string> coordinates; //x,y

	coordinates.insert(pair<string,string>("A","1,1"));
	coordinates.insert(pair<string,string>("B","11,2"));
	coordinates.insert(pair<string,string>("C","2,9"));
	coordinates.insert(pair<string,string>("D","8,13"));
	coordinates.insert(pair<string,string>("E","12,4"));
	coordinates.insert(pair<string,string>("F","0,7"));
	coordinates.insert(pair<string,string>("G","12,6"));
	coordinates.insert(pair<string,string>("H","7,14"));
	coordinates.insert(pair<string,string>("I","8,10"));
	coordinates.insert(pair<string,string>("J","6,13"));

	vector <double> distances[128][128];
	int i = 0;

	for (map<string, string>::iterator iter = coordinates.begin(); iter != coordinates.end(); ++iter) 
	{
		int j = 0;
		string coord1 = iter->second;
		
		char *nextToken = NULL;
		string coord1_x = strtok_s((char*)coord1.c_str(), ",", &nextToken);
		string coord1_y = nextToken;

		int coord1_x_int = atoi(coord1_x.c_str());
		int coord1_y_int = atoi(coord1_y.c_str());

		for (map<string, string>::iterator iter2 = coordinates.begin(); iter2 != coordinates.end(); ++iter2) 
		{
			string coord2 = iter2->second;
			
			string coord2_x = strtok_s((char*)coord2.c_str(), ",", &nextToken);
			string coord2_y = nextToken;

			int coord2_x_int = atoi(coord2_x.c_str());
			int coord2_y_int = atoi(coord2_y.c_str());

			double dist = sqrt(pow(coord1_x_int - coord2_x_int, 2) + pow(coord1_y_int - coord2_y_int, 2));
			
			distances[i][j].push_back(dist);
			j++; 
		}

		i++;
	}

	
	int min_distance_index = 0;
	
	string start_point = "A";
	string end_point = "B";

	string path = start_point+"->"; 
	string node;

	int start_node = 0;
		
	for(map<string, string>::iterator iter = coordinates.begin(); iter != coordinates.end(); iter++)
	{
		if(iter->first == start_point)
			break;
		else
			start_node++;
	}
		
	bool destination_reached = false;

	vector<int> hops_done;
	int hop_track = -1;

	double total_distance = 0;

	if(start_point == end_point)
	{
		path = start_point + "->" + end_point;
		// distance = 0
	}
	else
	{
		for (int trace = 0; trace < (int)coordinates.size(); trace ++)
		{
			double min_distance = MAX_DISTANCE;
			
			for(int hop = 0; hop<(int)coordinates.size(); hop++)
			{
				bool node_used_already = false;

				int k = 0;

				if (std::find(hops_done.begin(), hops_done.end(), hop) == hops_done.end())
				{
					if(distances[start_node][hop].at(0) - 0.0001 > 0.0001)
					{
						if(distances[start_node][hop].at(0) < min_distance)
						{
							min_distance = distances[start_node][hop].at(0);
							min_distance_index = hop;

							for (map<string, string>::iterator iter = coordinates.begin(); iter != coordinates.end(); ++iter) 
							{
								if(node_used_already)
									break;

								if(k == min_distance_index)
								{
									node = iter->first;
									if(path.find(node) != std::string::npos)
									{
										node = "";
										node_used_already = true;
										min_distance = MAX_DISTANCE;
										continue;
									}

									hop_track = hop;
									break;
								}

								k++;
							}
						} 
					} 
				}
			}

			hops_done.push_back(hop_track);

			total_distance += min_distance;

			if(coordinates.find(node) == coordinates.find(end_point))
			{
				// reached destination
				destination_reached = true;
			}

			if(destination_reached)
			{
				path += node; 
				break;
			}
			else
			{
				path += node + "->"; 
				start_node = min_distance_index;
			}
		}
	}

	cout << "Shortest Path = " << path << ". Total Distance = " << total_distance << endl; 
	
	return 0;
}
