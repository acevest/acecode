//
//  Meal.swift
//  FoodTracker
//
//  Created by Ace on 10/11/2016.
//  Copyright © 2016 Ace. All rights reserved.
//

import UIKit

class Meal {
    
    // MARK: Properties
    var name: String
    
    var photo: UIImage?
    
    var rating: Int
    
    
    // MARK: Initializtion
    
    init?(name: String, photo: UIImage?, rating: Int) {
        guard !name.isEmpty else {
            return nil
        }
        
        guard rating >= 0 else {
            return nil
        }
        
        self.name = name
        self.photo = photo
        self.rating = rating
    }
    
}
