// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "trailblazer.h"
#include "queue.h"
#include "set.h"
#include "pqueue.h"
#include "point.h"

using namespace std;

// this makes Path an alias for the type Vector<Vertex*>
typedef Vector<Vertex*> Path;

// the minimum difference for an alternate route
const double SUFFICIENT_DIFFERENCE = 0.2;

double difference(const Path &P, const Path &B );
bool contains(const Path&B, Vertex* v);
double calcCost(const Path &path, RoadGraph& graph);
Path searchPath(RoadGraph& graph, Vertex* start, Vertex* end, double (*heuristic)(RoadGraph& graph,Vertex* mid, Vertex* end));
double dijkstrasHeuristic(RoadGraph& graph, Vertex* mid, Vertex* end);

double aStarHeuristic(RoadGraph& graph,Vertex* mid, Vertex* end);

Path breadthFirstSearch(RoadGraph& graph, Vertex* start, Vertex* end) {

    Queue<Path> toDoList;
    Set<Vertex*> seenNodes;
    Path firstPath;
    firstPath.add(start);
    toDoList.enqueue(firstPath);
    start->setColor(YELLOW);

    while(!toDoList.isEmpty())
    {
        Path currPath = toDoList.dequeue();
        Vertex* currNode = currPath.get(currPath.size()-1);
        currNode->setColor(GREEN);

        if(currNode == end){
            return currPath;
        }

        else if(seenNodes.contains(currNode)){
            continue;
        }

        for(Vertex* neighbor : graph.getNeighbors(currNode)){
            if(!seenNodes.contains(neighbor)){

             Path newPath = currPath;
             newPath.add(neighbor);
             toDoList.enqueue(newPath);

            }
        }
        seenNodes.add(currNode);
        currNode->setColor(YELLOW);

    }

    return firstPath;
}

Path dijkstrasAlgorithm(RoadGraph& graph, Vertex* start, Vertex* end) {

    return searchPath(graph, start, end,dijkstrasHeuristic);
}


Path aStar(RoadGraph& graph, Vertex* start, Vertex* end) {

    return searchPath(graph, start, end, aStarHeuristic);
}

Path alternativeRoute(RoadGraph& graph, Vertex* start, Vertex* end) {

    Path optimalPath = dijkstrasAlgorithm(graph, start, end);

    Path alternativePath;

    int optimalCost = -1;

    cout <<"Optimal Path Cost: "<< calcCost(optimalPath,graph) <<  endl;

    for(int i=0; i < optimalPath.size()-1; i++){
        Edge* edge = graph.getEdge(optimalPath[i], optimalPath[i+1]);

        graph.removeEdge(edge);
        Path alternativeRoute = dijkstrasAlgorithm(graph, start, end);
        double alternativeCost = calcCost(alternativeRoute, graph);

        if(difference(alternativeRoute, optimalPath) >= SUFFICIENT_DIFFERENCE
                && ( optimalCost==-1 || alternativeCost< optimalCost )){
            optimalCost = alternativeCost;
            alternativePath = alternativeRoute;

            }

        graph.addEdge(edge);

        }

    return alternativePath;
}

double dijkstrasHeuristic(RoadGraph& graph, Vertex* mid, Vertex* end){
    return 0;
}

double aStarHeuristic(RoadGraph& graph,Vertex* mid, Vertex* end){
    return ((double)graph.getCrowFlyDistance(mid, end))/ graph.getMaxRoadSpeed();
}

Path searchPath(RoadGraph& graph, Vertex* start, Vertex* end, double (*heuristic)(RoadGraph& graph,Vertex* mid, Vertex* end)) {

    PriorityQueue<Path> toDoList;
    Path startPath;
    startPath.add(start);
    start->setColor(YELLOW);

    Set<Vertex*> seenNodes;
    toDoList.add(startPath, graph.getCrowFlyDistance(start, end)/ graph.getMaxRoadSpeed());

    while(!toDoList.isEmpty()){
        double priority = toDoList.peekPriority();
        Path currPath = toDoList.dequeue();
        Vertex* currNode = currPath.get(currPath.size()-1);
        currNode->setColor(GREEN);

        if(currNode== end){
            return currPath;
        }

        else if(seenNodes.contains(currNode)){
            continue;
        }

        for(Vertex* neighbor : graph.getNeighbors(currNode)){
            if(!seenNodes.contains(neighbor)){
                Path newPath = currPath;
                newPath.add(neighbor);
                neighbor->setColor(YELLOW);

                double newPriority = priority + graph.getEdge(currNode,neighbor)->cost + heuristic( graph ,neighbor, end);

                toDoList.enqueue(newPath, newPriority);
            }
        }

        seenNodes.add(currNode);
        currNode->setColor(GREEN);
    }

    Path emptyPath;
    return emptyPath;
}


double difference(const Path &P, const Path &B ){

    int nodesInBnotInP=0;

    for(Vertex* vert: P){
        if(!contains(B,vert)){
            nodesInBnotInP++;
        }
    }
    return ((double)nodesInBnotInP)/P.size();
}
bool contains(const Path&B, Vertex* v){
    for(Vertex* vert: B){
        if(vert->name==v->name){
            return true;
        }
    }

    return false;
}

double calcCost(const Path &path, RoadGraph& graph){
    double result = 0.0;
    for (int i = 1; i < path.size(); i++) {
        Edge* edge = graph.getEdge(path[i - 1], path[i]);
        result += edge->cost;
    }
    return result;
}
