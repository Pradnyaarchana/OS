#!/bin/bash

count=0
del=0
 
while true; do
    echo "Menu"
    echo "1. Create address book"
    echo "2. View address book."
    echo "3. Insert a record."
    echo "4. Delete a record."
    echo "5. Modify a record."
    echo "6. Exit"
#    echo "7. search by name/contact/city"
    echo "Enter choice: "
    read choice

    case $choice in 
       1)
            echo "Enter filename"
            read fileName
            if touch "$fileName"; then
            echo "Recordbook created successfully!"
            else
            echo "Error: Failed to create the address book. Please check permissions or the file path."
            fi
            ;;
        2)
            column -t -s $'\t' "$fileName"
            #cat $filename
            ;;
        
        #7)
	#	echo "Enter the search term (name, contact, or email): "
	#	read searchTerm
	#	grep -i "$searchTerm" "$fileName" || echo "No records found."
	# ;;
        
        3)
            echo "Enter number of records- " 
            read count
            i=0
            while [ $i -lt $count ]; do
                echo "Name: "
                read name

                echo "Contact Number: "
                read contact
                while ! [[ "$contact" =~ ^[7-9][0-9]{9}$ ]]; do
    			echo "Invalid contact number. Enter a 10-digit number: "
    			read contact
		done

                echo "city: "
                read city
                echo -e "$name\t$contact\t$city" >> "$fileName"
                echo 
                ((i++))
            done
            ;;
        
        4)
            echo "Enter the name to delete: "
            read delname
            sed -i "/$delname/d" "$fileName"
            ;;
        
        5)
            echo "Enter the name to modify: "
            read delname
            sed -i "/$delname/d" "$fileName"
            
            echo "Contact: "
            read contact
            echo "city: "
            read city
            echo -e "$delname\t$contact\t$city" >> "$fileName"
            ;;
        
        6)
            echo "Exiting..."
            exit 0
            ;;
        
        *)
            echo "Invalid choice, please try again."
            ;;
    esac
done