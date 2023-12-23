template<typename T>
void construct(T& world, Buffer& positions, Buffer& indices){
  //Fill the Buffers!

  std::vector<int> indbuf;
  std::vector<float> posbuf;

  std::function<void(std::vector<float>&, glm::vec3)> add = [](std::vector<float>& v, glm::vec3 p){
    v.push_back(p.x);
    v.push_back(p.y);
    v.push_back(p.z);
  };

  for(auto [cell, pos]: world.map ){
    
    if(world.map.oob(pos + glm::ivec2(1)))
      continue;

    float ha = cell.height;
    float hb = world.map.get(pos + glm::ivec2(1, 0))->height;
    float hc = world.map.get(pos + glm::ivec2(0, 1))->height;
    float hd = world.map.get(pos + glm::ivec2(1, 1))->height;

    if(std::abs(ha) > 1E3) continue;
    if(std::abs(hb) > 1E3) continue;
    if(std::abs(hc) > 1E3) continue;
    if(std::abs(hd) > 1E3) continue;
    
    //Add to Position Vector
    glm::vec3 a = glm::vec3(pos.x, cell.height, pos.y);
    glm::vec3 b = glm::vec3(pos.x+1, world.map.get(pos + glm::ivec2(1, 0))->height, pos.y);
    glm::vec3 c = glm::vec3(pos.x, world.map.get(pos + glm::ivec2(0, 1))->height, pos.y+1);
    glm::vec3 d = glm::vec3(pos.x+1, world.map.get(pos + glm::ivec2(1, 1))->height, pos.y+1);

    //UPPER TRIANGLE

    //Add Indices
    indbuf.push_back(posbuf.size()/3+0);
    indbuf.push_back(posbuf.size()/3+2);
    indbuf.push_back(posbuf.size()/3+1);

    add(posbuf, a);
    add(posbuf, b);
    add(posbuf, d);
    
    indbuf.push_back(posbuf.size()/3+0);
    indbuf.push_back(posbuf.size()/3+2);
    indbuf.push_back(posbuf.size()/3+1);

    add(posbuf, a);
    add(posbuf, d);
    add(posbuf, c);

  }

  indices.fill(indbuf);
  positions.fill(posbuf);

}
