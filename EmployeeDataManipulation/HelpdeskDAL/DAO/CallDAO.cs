using Microsoft.EntityFrameworkCore;
using System;
using System.Linq.Expressions;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;

namespace HelpdeskDAL
{
    public class CallDAO
    {
        readonly IRepository<Call> repo;

        public CallDAO()
        {
            repo = new HelpdeskRepository<Call>();
        }

        public async Task<Call> GetCallByEmployeeId(int empId)
        {
            return await repo.GetOne(gra => gra.EmployeeId == empId);
        }

        public async Task<Call> GetById(int id)
        {
            return await repo.GetOne(gra => gra.Id == id);
        }

        public async Task<List<Call>> GetAll()
        {
            return await repo.GetAll();
        }

        public async Task<int> Add(Call newCall)
        {
            return (await repo.Add(newCall)).Id;
        }

        public async Task<UpdateStatus> Update(Call updatedCall)
        {
            return await repo.Update(updatedCall);
        }
        public async Task<int> Delete(int id)
        {
            return await repo.Delete(id);
        }
    }
}