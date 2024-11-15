#pragma once

class QuadTreeNode {
      private:
	unsigned int  _level;
	Chunk	     *_chunk;
	QuadTreeNode *_children[4];
};
