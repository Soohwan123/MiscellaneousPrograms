using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;

namespace HelpdeskDAL
{
    public class EmployeeDAO
    {
        readonly IRepository<Employee> repo;

        public EmployeeDAO()
        {
            repo = new HelpdeskRepository<Employee>();
        }

        public async Task<Employee> GetbyEmail(string email)
        {
            return await repo.GetOne(emp => emp.Email == email);
        }
        public async Task<Employee> GetById(int id)
        {
            return await repo.GetOne(emp => emp.Id == id);
        }

        public async Task<List<Employee>> GetAll()
        {

            return await repo.GetAll();
        }

        public async Task<int> Add(Employee newEmployee)
        {
            return (await repo.Add(newEmployee)).Id;
        }

        public async Task<UpdateStatus> Update(Employee updatedEmployee)
        {
            return await repo.Update(updatedEmployee);
        }

        public async Task<int> Delete(int id)
        {
            return await repo.Delete(id);
        }
    }
}

