# DOD rules:

 1. IF YOU UNDERSTAND THE DATA, YOU UNDERSTAND THE PROBLEM.
 2. Everything is public.
 3. You have ONE entity_type of GameObject.
 4. You have ONE array of objects. Called "tables"
 5. Class methods are FORBIDDEN. Constructors are ok.
 6. Templates are forbidden(std::vector is ok)
 7. The GameObjects in the array are transformed by functions with the signature:
    void functionName(std::vector<Tables>& tables, int begin, int end, ...)
 8. If's inside function myst be avoided, SORT THE ARRAY and iterate the part of it you are interested
    As an example, if you want to draw only the visible objects, don't do
    ```C
    for(int i = begin; i < end; i++){
        if(tables[i].visible) draw(tables[i]);
    }
    ```

    first SORT the tables by visible attribute, and then iterate all the visible gameObjects.
    ```C
    std::sort(tables, (GameObject* a, GameObject* b)-> int { return a->visible - b->visible; }); // note, you can also sort by z-index
    ```
    
    then, since all the visible objects are at the end, get the first visible object index, and iterate from there
    ```C
    int firstVisibleIndex = findFirstVisible(tables);

    for(int i = firstVisibleIndex; i < tables.size(); i++){
        draw(tables[i]);
    }
    ```
    Sort and iterate, don't "if"

 # On threads
 
 Be aware of "false sharing" when using threads:
 
 1. If you have 2 or more threads that access the same data
 2. And one or more of them genetrates a write operation on this data.
 3. Very fast(like, inside a loop).
 
 You are invalidating the cache *FOR ALL THREADS THAT ACCESS THAT DATA!!!*.
 
 Use buffers and write all the calculation in the last minute.