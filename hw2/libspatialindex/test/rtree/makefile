#.PHONY= RTreeQuery
#includeFolder=~/spatialBuild/usr/local/include/
#toolsFolder=~/libspatialindex/src/tools/
#parent=~
#RTreeQuery: RTreeQuery.cc
#	g++ -c -std=c++0x RTreeQuery.cc -I $(includeFolder)
#	g++ -c -std=c++0x -I $(includeFolder) ~/libspatialindex/src/storagemanager/DiskStorageManager.cc
#	g++ -c -std=c++0x -I $(includeFolder) -I $(toolsFolder) -c ~/libspatialindex/src/tools/Tools.cc
#	g++ -c -std=c++0x -I $(includeFolder) ~/libspatialindex/src/storagemanager/RandomEvictionsBuffer.cc
#	g++ -c -std=c++0x -I $(includeFolder) ~/libspatialindex/src/storagemanager/Buffer.cc
#	g++ -c -std=c++0x -I $(includeFolder) ~/libspatialindex/src/spatialindex/Region.cc
#	g++ -c -std=c++0x -I $(includeFolder) ~/libspatialindex/src/spatialindex/LineSegment.cc
#	g++ -c -std=c++0x -I $(includeFolder) ~/libspatialindex/src/spatialindex/Point.cc
#	g++ -c -std=c++0x -I $(includeFolder) ~/libspatialindex/src/spatialindex/SpatialIndexImpl.cc
#	g++ -c -std=c++0x -I $(includeFolder) ~/libspatialindex/src/rtree/RTree.cc
#	g++ -c -std=c++0x -I $(includeFolder) ~/libspatialindex/src/rtree/Statistics.cc
#	g++ -c -std=c++0x -I $(includeFolder) ~/libspatialindex/src/rtree/Leaf.cc
#	g++ -c -std=c++0x -I $(includeFolder) ~/libspatialindex/src/rtree/Node.cc
#	g++ -c -std=c++0x -I $(includeFolder) ~/libspatialindex/src/rtree/BulkLoader.cc
#	g++ -c -std=c++0x -I $(includeFolder) ~/libspatialindex/src/rtree/Index.cc
#	g++ -c -std=c++0x -I $(includeFolder) ~/libspatialindex/src/capi/IdVisitor.cc
#	g++ RTreeQuery.o DiskStorageManager.o Tools.o RandomEvictionsBuffer.o Region.o Point.o RTree.o Buffer.o SpatialIndexImpl.o LineSegment.o Statistics.o Leaf.o Node.o BulkLoader.o Index.o IdVisitor.o -o MyQuery
# .PHONY= MyQuery
# parent=~
# parent=~/Documents/Sem5/COL761/Assignments/COL761Assignments/hw2/
parent=../../..
# includeFolder=$(parent)/spatialBuild/usr/local/include/
includeFolder=$(parent)/libspatialindex/include/
toolsFolder=$(parent)/libspatialindex/src/tools/
MyQuery: MyQuery.o Tools.o RandomEvictionsBuffer.o Region.o Point.o RTree.o Buffer.o SpatialIndexImpl.o LineSegment.o Statistics.o Leaf.o Node.o BulkLoader.o Index.o IdVisitor.o MemoryStorageManager.o
	g++ MyQuery.o Tools.o RandomEvictionsBuffer.o Region.o Point.o RTree.o Buffer.o SpatialIndexImpl.o LineSegment.o Statistics.o Leaf.o Node.o BulkLoader.o Index.o IdVisitor.o MemoryStorageManager.o -o MyQuery
MyQuery.o: MyQuery.cc	
	g++ -c -std=c++0x MyQuery.cc -I $(includeFolder)
clean: 
	rm *.o MyQuery
# obj: 
# 	g++ -c -std=c++0x RTreeQuery.cc -I $(includeFolder)
# 	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/storagemanager/DiskStorageManager.cc
MemoryStorageManager.o: $(parent)/libspatialindex/src/storagemanager/MemoryStorageManager.cc
	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/storagemanager/MemoryStorageManager.cc
Tools.o: $(parent)/libspatialindex/src/tools/Tools.cc
	g++ -c -std=c++0x -I $(includeFolder) -I $(toolsFolder) -c $(parent)/libspatialindex/src/tools/Tools.cc
RandomEvictionsBuffer.o: $(parent)/libspatialindex/src/storagemanager/RandomEvictionsBuffer.cc
	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/storagemanager/RandomEvictionsBuffer.cc
Buffer.o: $(parent)/libspatialindex/src/storagemanager/Buffer.cc
	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/storagemanager/Buffer.cc
Region.o: $(parent)/libspatialindex/src/spatialindex/Region.cc
	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/spatialindex/Region.cc
LineSegment.o: $(parent)/libspatialindex/src/spatialindex/LineSegment.cc
	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/spatialindex/LineSegment.cc
Point.o: $(parent)/libspatialindex/src/spatialindex/Point.cc
	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/spatialindex/Point.cc
SpatialIndexImpl.o: $(parent)/libspatialindex/src/spatialindex/SpatialIndexImpl.cc
	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/spatialindex/SpatialIndexImpl.cc
RTree.o: $(parent)/libspatialindex/src/rtree/RTree.cc
	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/rtree/RTree.cc
Statistics.o: $(parent)/libspatialindex/src/rtree/Statistics.cc
	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/rtree/Statistics.cc
Leaf.o: $(parent)/libspatialindex/src/rtree/Leaf.cc
	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/rtree/Leaf.cc
Node.o: $(parent)/libspatialindex/src/rtree/Node.cc
	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/rtree/Node.cc
BulkLoader.o: $(parent)/libspatialindex/src/rtree/BulkLoader.cc
	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/rtree/BulkLoader.cc
Index.o: $(parent)/libspatialindex/src/rtree/Index.cc
	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/rtree/Index.cc
IdVisitor.o: $(parent)/libspatialindex/src/capi/IdVisitor.cc
	g++ -c -std=c++0x -I $(includeFolder) $(parent)/libspatialindex/src/capi/IdVisitor.cc
