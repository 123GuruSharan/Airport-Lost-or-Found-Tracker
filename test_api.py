import requests
import json

def test_report_endpoint():
    """Test the /report endpoint"""
    url = "http://localhost:18080/report"
    headers = {"Content-Type": "application/json"}
    
    # Test data for reporting a lost item
    data = {
        "id": 101,
        "description": "Test Lost Item - Black Wallet",
        "location": "Terminal A, Gate 5",
        "date": "2025-08-29",
        "isLost": True,
        "reportedBy": "John Doe",
        "contactInfo": "john.doe@example.com",
        "tags": "wallet, black, leather",
        "notes": "Contains ID cards and credit cards"
    }
    
    try:
        response = requests.post(url, headers=headers, json=data)
        print(f"Report Endpoint Test:")
        print(f"Status Code: {response.status_code}")
        print(f"Response: {response.text}")
        print("-" * 50)
        return response.status_code == 200
    except Exception as e:
        print(f"Error testing report endpoint: {e}")
        return False

def test_search_endpoint():
    """Test the /search endpoint"""
    url = "http://localhost:18080/search"
    headers = {"Content-Type": "application/json"}
    
    # Test search by description
    search_data = {
        "description": "wallet"
    }
    
    try:
        response = requests.post(url, headers=headers, json=search_data)
        print(f"Search Endpoint Test:")
        print(f"Status Code: {response.status_code}")
        print(f"Response: {response.text}")
        print("-" * 50)
        return response.status_code == 200
    except Exception as e:
        print(f"Error testing search endpoint: {e}")
        return False

def test_search_by_id():
    """Test searching by ID"""
    url = "http://localhost:18080/search"
    headers = {"Content-Type": "application/json"}
    
    # Test search by ID
    search_data = {
        "id": 101
    }
    
    try:
        response = requests.post(url, headers=headers, json=search_data)
        print(f"Search by ID Test:")
        print(f"Status Code: {response.status_code}")
        print(f"Response: {response.text}")
        print("-" * 50)
        return response.status_code == 200
    except Exception as e:
        print(f"Error testing search by ID: {e}")
        return False

def test_invalid_json():
    """Test with invalid JSON"""
    url = "http://localhost:18080/report"
    headers = {"Content-Type": "application/json"}
    
    # Invalid JSON data
    invalid_data = "This is not valid JSON"
    
    try:
        response = requests.post(url, headers=headers, data=invalid_data)
        print(f"Invalid JSON Test:")
        print(f"Status Code: {response.status_code}")
        print(f"Response: {response.text}")
        print("-" * 50)
        return response.status_code == 400  # Should return 400 for bad request
    except Exception as e:
        print(f"Error testing invalid JSON: {e}")
        return False

if __name__ == "__main__":
    print("Testing Airport Lost & Found API Endpoints")
    print("=" * 50)
    
    # Run all tests
    tests = [
        test_report_endpoint,
        test_search_endpoint,
        test_search_by_id,
        test_invalid_json
    ]
    
    results = []
    for test in tests:
        results.append(test())
    
    print("\nTest Results Summary:")
    print("=" * 50)
    for i, (test, result) in enumerate(zip(tests, results), 1):
        status = "PASS" if result else "FAIL"
        print(f"Test {i}: {test.__name__} - {status}")
    
    print(f"\nOverall: {sum(results)}/{len(results)} tests passed")
