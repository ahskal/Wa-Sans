#pragma once
#pragma once

#define HouseCount 20
class VillageMap : public Actor
{
public:
    static VillageMap* Create(string name = "VillageMap");
private:
    class Camera* cam;
    //class House* house[4];

    class House* house[HouseCount];
    bool HouseRender;
    bool HouseLateUpdate;
    
    class House* house2;

    






public:

private:
    VillageMap();
    virtual ~VillageMap();
public:
    //기존 Actor 변수를 오버라이드 하는코드
    void    Release()override;
    void	Update() override;
    void    Render() override;

    //새로 생성한 맵에 
    void    Init();
    void	LateUpdate();
    void    Hierarchy();
    void    ResizeScreen();

    Camera* GetCam() const { return cam; }

};



