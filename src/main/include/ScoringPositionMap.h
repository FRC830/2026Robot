#pragma once

#include <unordered_map>
#include <array>
#include <frc/Filesystem.h>
#include <wpi/json.h>
#include <fstream>
#include <fmt/core.h>

enum class ScoringLocation 
{
    L1_RIGHT = 0, L1_LEFT = 1, L2_RIGHT = 2, L2_LEFT = 3
};

class ScoringPositionMap 
{
public:
    ScoringPositionMap() 
    {
        LoadFromJSON();
    }

    // Location returned in meters and degrees (X, Y, deg)
    std::array<double, 3> getPosition(int tag_id, ScoringLocation loc) const 
    {
        // Check if the tag_id exists in the data map
        auto it = _scoring_location_map.find(tag_id);
        if (it == _scoring_location_map.end()) 
        {
            return INVALID_LOCATION;
        }

        // Return the requested array based on the position enum
        const auto& outerArray = it->second;
        return outerArray[static_cast<int>(loc)];
    }

    bool isValidLocation(std::array<double, 3>& loc)
    {
        return loc[0] > 0.0f && loc[1] > 0.0f;
    }

private:
    void LoadFromJSON() 
    {
        // Get deploy directory path
        std::string deployPath = frc::filesystem::GetDeployDirectory();
        std::string filePath = deployPath + "/scoring_positions.json";
        
        std::ifstream file(filePath);
        if (!file.is_open()) {
            fmt::print("WARNING: Could not open {}. Using fallback hardcoded positions.\n", filePath);
            LoadFallbackPositions();
            return;
        }
        
        try {
            wpi::json j;
            file >> j;
            
            // Parse JSON into the map
            for (auto& [tag_id_str, locations] : j["positions"].items()) {
                int tag_id = std::stoi(tag_id_str);
                
                std::array<std::array<double, 3>, 4> positions;
                positions[0] = ParsePosition(locations["L1_RIGHT"]);
                positions[1] = ParsePosition(locations["L1_LEFT"]);
                positions[2] = ParsePosition(locations["L2_RIGHT"]);
                positions[3] = ParsePosition(locations["L2_LEFT"]);
                
                _scoring_location_map[tag_id] = positions;
            }
            
            fmt::print("ScoringPositionMap: Loaded {} tag positions from JSON\n", _scoring_location_map.size());
        }
        catch (const std::exception& e) {
            fmt::print("ERROR loading scoring positions: {}. Using fallback.\n", e.what());
            LoadFallbackPositions();
        }
    }
    
    std::array<double, 3> ParsePosition(const wpi::json& pos) 
    {
        return {pos[0].get<double>(), pos[1].get<double>(), pos[2].get<double>()};
    }
    
    void LoadFallbackPositions() 
    {
        // Original hardcoded values as fallback
        _scoring_location_map[6] = {{{13.953003894899778, 3.201331411670378, 120.0},{13.667042306570156, 3.036231411670378, 120.0},{13.953003894899778, 3.201331411670378, 120.0},{13.667042306570156, 3.036231411670378, 120.0}}};
        _scoring_location_map[7] = {{{14.220697999999999, 4.38785, 180},{14.220697999999999, 4.05765, 180},{14.220697999999999, 4.38785, 180},{14.220697999999999, 4.05765, 180}}};
        _scoring_location_map[8] = {{{13.326088105100222, 5.212418588329622, -120.0},{13.612049693429844, 5.047318588329621, -120.0},{13.326088105100222, 5.212418588329622, -120.0},{13.612049693429844, 5.047318588329621, -120.0}}};
        _scoring_location_map[9] = {{{12.164800105100221, 4.850468588329622, -60.000000000000014},{12.450761693429843, 5.0155685883296215, -60.000000000000014},{12.164800105100221, 4.850468588329622, -60.000000000000014},{12.450761693429843, 5.0155685883296215, -60.000000000000014}}};
        _scoring_location_map[10] = {{{11.897105999999999, 3.6639500000000003, 0.0},{11.897105999999999, 3.99415, 0.0},{11.897105999999999, 3.6639500000000003, 0.0},{11.897105999999999, 3.99415, 0.0}}};
        _scoring_location_map[11] = {{{12.791715894899777, 2.8393814116703777, 59.999999999999986},{12.505754306570156, 3.004481411670378, 59.999999999999986},{12.791715894899777, 2.8393814116703777, 59.999999999999986},{12.505754306570156, 3.004481411670378, 59.999999999999986}}};
        _scoring_location_map[17] = {{{4.222263894899776, 2.8393814116703777, -120.00000000000001},{3.936302306570155, 3.004481411670378, -120.00000000000001},{4.222263894899776, 2.8393814116703777, -120.00000000000001},{3.936302306570155, 3.004481411670378, -120.00000000000001}}};
        _scoring_location_map[18] = {{{3.3274, 3.6639500000000003, 180.0},{3.3274, 3.99415, 180.0},{3.3274, 3.6639500000000003, 180.0},{3.3274, 3.99415, 180.0}}};
        _scoring_location_map[19] = {{{3.5953481051002214, 4.850468588329622, 119.99999999999999},{3.881309693429843, 5.0155685883296215, 119.99999999999999},{3.5953481051002214, 4.850468588329622, 119.99999999999999},{3.881309693429843, 5.0155685883296215, 119.99999999999999}}};
        _scoring_location_map[20] = {{{4.756382105100222, 5.212418588329622, 59.99999999999999},{5.042343693429844, 5.047318588329621, 59.99999999999999},{4.756382105100222, 5.212418588329622, 59.99999999999999},{5.042343693429844, 5.047318588329621, 59.99999999999999}}};
        _scoring_location_map[21] = {{{5.6512459999999995, 4.38785, 0.0},{5.6512459999999995, 4.05765, 0.0},{5.6512459999999995, 4.38785, 0.0},{5.6512459999999995, 4.05765, 0.0}}};
        _scoring_location_map[22] = {{{5.383297894899777, 3.201331411670378, -59.99999999999999},{5.097336306570155, 3.036231411670378, -59.99999999999999},{5.383297894899777, 3.201331411670378, -59.99999999999999},{5.097336306570155, 3.036231411670378, -59.99999999999999}}};
        fmt::print("ScoringPositionMap: Using fallback hardcoded positions\n");
    }
    
    std::unordered_map<int, std::array<std::array<double, 3>, 4>> _scoring_location_map;

    const std::array<double, 3> INVALID_LOCATION = {-1.0, -1.0, 0.0};
};
