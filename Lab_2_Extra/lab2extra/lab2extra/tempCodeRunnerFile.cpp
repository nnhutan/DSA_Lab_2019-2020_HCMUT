int n = graph.size();
	vector<int> color(n);
	queue<int> q;
	q.push(0);
	color[0] = 1;
	while(q.size()){
		for(auto i:graph[q.front()]){
			if(color[i]){
				if(color[i]==color[q.front()])
					return false;
				continue;
			}
			color[i] = -color[q.front()];
			q.push(i);
		}
		q.pop();
	}
	return true;