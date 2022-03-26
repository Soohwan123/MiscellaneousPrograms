using Microsoft.EntityFrameworkCore;
using System;
using System.Linq.Expressions;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;

namespace HelpdeskDAL
{
    public class ProblemDAO
    {
        readonly IRepository<Problem> repo;

        public ProblemDAO()
        {
            repo = new HelpdeskRepository<Problem>();
        }

        public async Task<List<Problem>> GetAll()
        {
            return await repo.GetAll();
        }

        public async Task<Problem> GetByDescription(string des)
        {
            return await repo.GetOne(gra => gra.Description == des);
        }
    }
}